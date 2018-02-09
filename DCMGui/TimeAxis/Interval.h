#ifndef INTERVAL_H
#define INTERVAL_H

#include "DSGuiGlobal.h"
#include <QList>

class Interval;
typedef QList<Interval>  IntervalList;
class Interval
{
public:
	qint64 start,end;
	Interval(qint64 s,qint64 e):start(s),end(e){}
	Interval():start(0),end(0){}
	inline bool valid() const;
	inline void reset();
	inline qint64 interval()const;
	//-1,小于该区间；1,大于该区间；=0,包含
	inline int contain(qint64 time) const;
	inline bool operator<(const Interval&that) const;
	inline bool operator==(const Interval&that) const;
	inline Interval intersect(const Interval&)const;
	inline IntervalList unintersect(const Interval&)const;
	//返回有交集的区间集合，mergedInvs必须为合并有序区间集合
	IntervalList intersect(const IntervalList& mergedInvs) const;
	//消除与mergerdInvs有交集的片段，mergedInvs必须为合并有序区间集合，返回结果为this的子集
	IntervalList unintersect(const IntervalList& mergedInvs) const;

	//区间合并,返回合并后的有序区间集合
	static IntervalList merge(IntervalList& invs);
	//返回与reg有交集的区间集合,mergedInvs必须为有序区间集合
	static IntervalList intersect(const Interval& reg, const IntervalList& mergedInvs);
	//消除集合srcInvs与cmpList的交集，必须都是合并有序区间集合，返回srcInvs的子集合
	static IntervalList unintersect(const IntervalList& srcInvs, const IntervalList& cmpList);
};

inline bool Interval::valid() const
{
	return start>=0 && end>start;
}

inline void Interval::reset()
{
	end = start = 0;
}

inline qint64 Interval::interval() const
{
	return (end-start);
}

inline bool Interval::operator<(const Interval&that) const
{
	return this->start < that.start;
}

inline bool Interval::operator==(const Interval&that) const
{
	return this->start == that.start && this->end == that.end;
}

inline int Interval::contain(qint64 time) const
{
	if(time>end)
		return 1;
	if(time<start)
		return -1;
	return 0;
}

inline Interval Interval::intersect( const Interval& that) const
{
	if(start>=that.end || end<=that.start)
	{
		return Interval();
	}
	return Interval(qMax(start,that.start),qMin(end,that.end));
}

inline IntervalList Interval::unintersect( const Interval& that) const
{
	IntervalList listRet;
	if(start>=that.end || end<=that.start)
	{
		listRet.push_back(*this);
		return listRet;
	}	
	if(end<=that.end && start>=that.start)
	{
		return listRet;  //空
	}
	if(end>that.end && start < that.start)
	{
		listRet.push_back(Interval(start,that.start));
		listRet.push_back(Interval(that.end,end));
		return listRet;
	}
	if(start<that.start)
	{
		listRet.push_back(Interval(start,that.start));
		return listRet;
	}
	if(end>that.end)
	{
		listRet.push_back(Interval(that.end,end));
		return listRet;
	}
	return listRet;
}

DS_GUI_EXPORT QDebug operator<<( QDebug dbg, const Interval &vector );
DS_GUI_EXPORT QDebug operator<<( QDebug dbg, const IntervalList &vector );

#endif // 
