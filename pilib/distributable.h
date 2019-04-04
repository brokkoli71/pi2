#pragma once

#include <vector>
#include <string>

#include "argumentdatatype.h"
#include "distributor.h"

using std::vector;
using std::string;

namespace pilib
{

	class PISystem;

	/**
	Base class for commands that can distribute themselves to multiple processes.
	*/
	class Distributable
	{
	public:
		/**
		Run this command in distributed manner.
		@return Output from each sub-job.
		*/
		virtual vector<string> runDistributed(Distributor& distributor, vector<ParamVariant>& args) const = 0;

		vector<string> runDistributed(Distributor& distributor, std::initializer_list<ParamVariant> args) const
		{
			vector<ParamVariant> vargs;
			vargs.insert(vargs.end(), args.begin(), args.end());
			return runDistributed(distributor, vargs);
		}

		/**
		Calculate amount of extra memory required by the command as a fraction of total size of all input and output images.
		@return extraMemFactor so that total memory needed per node or process = sum((block size) * (pixel size in bytes)) * (1 + extraMemFactor), where the sum is taken over all argument images.
		*/
		virtual double calculateExtraMemory(vector<ParamVariant>& args) const
		{
			return 0.0;
		}

		/**
		This function is given coordinates of a block in reference image (first output image in argument list or first input if there are no outputs)
		and it determines the corresponding block in another argument image.
		If this method does nothing, it is assumed that the argument image can be divided similarly than the reference image.
		@param argIndex Index of argument image.
		@param readStart, readSize File position and size of data that is loaded from disk for the reference output. Relevant only for Input and InOut images.
		@param writeFilePos, writeImPos, writeSize File position, image position and size of valid data generated by the command for the given block. Relevant only for Output and InOut images.
		*/
		virtual void getCorrespondingBlock(vector<ParamVariant>& args, size_t argIndex, Vec3c& readStart, Vec3c& readSize, Vec3c& writeFilePos, Vec3c& writeImPos, Vec3c& writeSize) const
		{

		}

		/**
		Gets the execution time rating for this task.
		Returns JobType::Normal by default.
		*/
		virtual JobType getJobType() const
		{
			return JobType::Normal;
		}
	};
}
