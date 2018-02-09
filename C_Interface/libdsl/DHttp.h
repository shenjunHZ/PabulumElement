/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2012-12
 *
 * DHttp.h : Http�����⣬��װһ��HTTP Message������body��header
 */

#ifndef INCLUDED_LIBDSL_DHTTP_H
#define INCLUDED_LIBDSL_DHTTP_H

#include <libdsl/dslbase.h>
#include <libdsl/DStr.h>
#include <libdsl/DRefObj.h>

#include <map>
#include <vector>

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

enum {
	DHTTP_AUTH_UNKNOWN = 0,
	DHTTP_AUTH_BASIC_AUTHEN,   // ����˷��͸��ͻ��˵�Basic��֤����
	DHTTP_AUTH_BASIC_AUTHOR,   // �ͻ��˷��͸�����˵�Basic��֤Ӧ��
	DHTTP_AUTH_DIGEST_AUTHEN,  // ����˷��͸��ͻ��˵�Digest��֤����
	DHTTP_AUTH_DIGEST_AUTHOR,  // �ͻ��˷��͸�����˵�Digest��֤Ӧ��
};

class LIBDSL_API DHttpAuthInfo
{
public:
	int m_type;
	DStr m_realm;
	DStr m_username;
	// �����ֶν�����Basic
	DStr m_password; // ����
	// �����ֶν�����Digest
	DStr m_nonce;    // ��������ɵ�����ִ����������
	DStr m_opaque;   // ��������ã��ͻ���ԭ�����أ����������
	DStr m_uri;      // �����URI�ַ������������
	DStr m_qop;      // Ϊ�գ�����ȡֵ��auth��
	DStr m_nc;       // qopȡֵ��auth��ʱ��Ч�����ڷ�ֹ�ط�
	DStr m_cnonce;   // qopȡֵ��auth��ʱ��Ч���ͻ������ɵ�����ִ����������
	DStr m_response; // �������ɵ�Ӧ��
	DStr m_method;   // GET/PUT�ȷ������ƣ��������
public:
	DHttpAuthInfo() : m_type( DHTTP_AUTH_UNKNOWN ) {}
	void Reset();
	inline int Parse( const DStr & name, const DStr & value ) { return Parse( name.c_str(), value.c_str() ); }
	int Parse( const char * name, const char * value );
	static int ReadParam( const char * str, DStr * name, DStr * value );
	int Output( DStr * name, DStr * value ) const;
	
	inline int SetBasicAuthen( const DStr & realm ) { return SetBasicAuthen( realm.c_str() ); }
	int SetBasicAuthen( const char * realm );
	inline int SetBasicAuthor( const DStr & username, const DStr & password ) { return SetBasicAuthor( username.c_str(), password.c_str() ); }
	int SetBasicAuthor( const char * username, const char * password );
	inline int SetDigestAuthen( const DStr & realm, const DStr & qop = DStr(), const DStr & nonce = DStr(), const DStr & opaque = DStr() )
	{
		return SetDigestAuthen( realm.c_str(), qop.c_str(), nonce.c_str(), opaque.c_str() );
	}
	int SetDigestAuthen( const char * realm, const char * qop = NULL, const char * nonce = NULL, const char * opaque = NULL );
	// ����SetDigestAuthor()֮ǰ��Authen��ص��ֶ�Ҫ��ֵ������passwordҪ�������ĵ�ֵ
	inline int SetDigestAuthor( const DStr & username, const DStr & password, const DStr & method, const DStr & uri, 
		const DStr & nc = DStr(), const DStr & cnonce = DStr() )
	{
		return SetDigestAuthor( username.c_str(), password.c_str(), method.c_str(), uri.c_str(), nc.c_str(), cnonce.c_str() );
	}
	int SetDigestAuthor( const char * username, const char * password, const char * method, const char * uri, 
			const char * nc = NULL, const char * cnonce = NULL );
	static DStr GenerateRandStr();
	// ����Digest��HA1����MD5��user ":" realm ":" password��
	static inline DStr GenerateHA1( const DStr & username, const DStr & realm, const DStr & password )
	{
		return GenerateHA1( username.c_str(), realm.c_str(), password.c_str() );
	}
	static DStr GenerateHA1( const char * username, const char * realm, const char * password );
	inline DStr GenerateDigest( const DStr & ha1 ) const { return GenerateDigest( ha1.c_str() ); }
	DStr GenerateDigest( const char * ha1 ) const;

	// ��֤AUTHOR������Digest��password���������Ļ���HA1
	inline bool CheckAuthor( const DStr & username, const DStr & password ) const
	{
		return CheckAuthor( username.c_str(), password.c_str() );
	}
	bool CheckAuthor( const char * username, const char * password ) const;
};

// DHttp���header��body�Ƿֿ������໥��Ӱ��
// �����DHTTP_FLAG_UPDATE_CONTENT_LENGTH�����ˣ�ȱʡ�����ã�
// �򵱸���body����ʱ�����Զ�����header��Content-Length��ֵ������֮��Ȼ��
// ȱʡ���ã����㹹������͵�http message������parse���յ���http message��һ��Ҫ��ʽ�ر�
#define DHTTP_FLAG_UPDATE_CONTENT_LENGTH	(1<<0)  

class LIBDSL_API DHttp : virtual public dsl::DRefObj
{
public:
	DHttp();
	~DHttp();

	// fname���ļ���������չ������ index.html �� html������minetypeֵ��text/html
	static const char * GetFileMimeType( const char * fname );
	static const char * GetStatusStr( int status );

public:
	/**
	 * ��λ����
	 */
	void Reset();

	int GetFlag() const { return m_flag; }
	void SetFlag( int flag ) { m_flag = flag; return; }

public: // header �Ĵ���
	/**
	 * �����л����ݣ�����Http Header�����DHttp�ṹ�� 
	 * @param data �������ݵ��׵�ַ
	 * @param len �������ݵĳ��ȣ����Ϊ������ʾ���������Ϊ�ַ����������ڲ����Զ������ַ�����β
	 * @return �������������ݳ������Ϸ��ı���
	 *            0��header���岻���������������ȫ�����ģ��ȴ���������
	 *         ����������header��������ϣ����ر������ĵ����ݳ���
	 */
	// DSL_DEPRECATED int fromStream(const char * data, int len = -1);
	int ParseHeader(const DStr & data);
	int ParseHeader(const char * data, int len = -1);

	/**
	 * �ж��Ƿ�Ϊ�����
	 * @return true:����� false:�ظ���
	 */
	bool IsRequest() const;

	/**
	 * ��ȡЭ��ķ���
	 * @return Э������ �� GET POST ...
	 */
	const char * GetMethod() const;

	/**
	 * ��ȡURL
	 * @return URL�ֶ�
	 */
	const char * GetUrl() const;

	/**
	 * ��ȡ״̬��
	 * @return ״̬��
	 */
	int GetStatus() const;

	/**
	 * ��ȡ״̬�������ֶ�
	 * @return ״̬�������ֶ�
	 */
	const char * GetReason() const;

	/**
	 * ��ȡ�汾��
	 * @return �汾��
	 */
	const char * GetVersion() const;

	/**
	 * ��ȡͷ����Ϣ
	 * @param key ͷ���key
	 * @return ͷ���value
	 */
	// const char * GetHeadParam(const char * headKey) const; // ��ȡͷ����Ϣ
	const char * GetHeader(const char * key) const; // ��ȡͷ����Ϣ
	
	/**
	 * ��ȡ��֤��Ϣ�������DHttpAuthInfo��
	 */
	int GetHeaderAuth( DHttpAuthInfo * auth );

	/**
	 * �������������������
	 * @param requestLine �������� ���� method url version ���� POST / HTTP/1.1
	 * @return 0���ɹ�  ������ʧ��
	 */

	int SetRequestLine(const char * method, const char * url, const char * version);

	/**
	 * ���ûظ�������������
	 * @param responseLine �������� ���� version status reason ���� HTTP/1.1 200 OK
	 * @return 0���ɹ�  ������ʧ��
	 */
	// int SetResponseLine(const char * responseLine);
	int SetResponseLine(const char * version, int status, const char * reason );

	/**
	 * ����ͷ������
	 * @param headKey ͷ���key
	 * @param headValue ͷ���value
	 * @return 0���ɹ�  ������ʧ��
	 */
	int SetHeader(const char * head, const char * value);

	/**
	 * ������֤��Ϣ
	 */
	int SetHeaderAuth( const DHttpAuthInfo & auth );

	/**
	 * ���л�����
	 * @param buf ����������������л��������
	 * @param maxlen ������������ջ���Ĵ�С
	 * @return > 0 ���л���ĳ���  ������ʧ��
	 */
	int OutputHeader( char * buf, int maxlen ) const;
	int OutputHeader( DStr * buf ) const;
	DStr OutputHeader() const;

public:  // body�Ĵ���
	/**
	 * ��ȡHTTP���峤��
	 * @return HTTP���峤��
	 */
	int GetBodyLen() const;	// ��ȡHTTP���峤��

	/**
	 * ��ȡHTTP����
	 * @return HTTP������׵�ַ
	 */
	const char * GetBody() const; // ��ȡHTTP����

	/**
	 * ����HTTP��������
	 * @param data ���ݵ�Դ��ַ
	 * @param len ���ݵĳ��ȣ����Ϊ������ʾ���������Ϊ�ַ����������ڲ����Զ������ַ�����β
	 * @return 0���ɹ�  ������ʧ��
	 */
	int SetBody(const char * data, int len = -1);
	int AppendBody(const char * data, int len = -1);

	int SetBodyLen( int len );
	char * GetBodyBuf();

protected:
	int parse_first_line(char * data);
	int parse_head_line(char * data);

protected:
	int 		m_flag;
	dsl::DStr	m_recvHead;		// ���յ�����������header����

	bool		m_isRequest;
	dsl::DStr	m_method;
	dsl::DStr	m_url;
	dsl::DStr	m_version;
	int			m_status;
	dsl::DStr	m_reason;

	// FIXME : header��name�Ǵ�Сд�����е�
	std::map<dsl::DStr, dsl::DStr, dsl::DStrCaseCompare> m_headers;

	std::vector<char> m_body;  // ���body���ݣ���ʵ�ʳ��ȶ�1�ֽڣ���֤'\0'����
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSL_DHTTP_H
