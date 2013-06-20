/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Written (W) 2013 Soumyajit De
 */

#ifndef INDEPENDENT_JOB_H_
#define INDEPENDENT_JOB_H_

#include <shogun/lib/config.h>
#include <shogun/base/SGObject.h>
#include <shogun/lib/computation/job/JobResultAggregator.h>

namespace shogun
{

/** @brief Abstract base for general computation jobs to be registered
 * in CIndependentComputationEngine. compute method produces a job result
 * and submits it to the internal JobResultAggregator. Each set of jobs
 * that form a result will share the same job result aggregator.
 */
class CIndependentJob : public CSGObject
{
public:
	/** default constructor, no args */
	CIndependentJob()
	: CSGObject(), m_aggregator(NULL)
	{
		SG_GCDEBUG("%s created (%p)\n", this->get_name(), this)
	}

	/** default constructor, one arg */
	CIndependentJob(CJobResultAggregator* aggregator)
	: CSGObject(), m_aggregator(aggregator)
	{
		SG_REF(m_aggregator);
		SG_GCDEBUG("%s created (%p)\n", this->get_name(), this)
	}

	/** destructor */
	virtual ~CIndependentJob()
	{
		SG_UNREF(m_aggregator);
		SG_GCDEBUG("%s destroyed (%p)\n", this->get_name(), this)
	}

	/** abstract compute method that computes the job, creates a CJobResult,
	 * submits the result to the job result aggregator
	 */
	virtual void compute() = 0;

	/** @return object name */
	virtual const char* get_name() const
	{
		return "CIndependentJob";
	}
protected:
	/** the job result aggregator for the current job */
	CJobResultAggregator* m_aggregator;
};

}

#endif // INDEPENDENT_JOB_H_
