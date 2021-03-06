/*
 * AdaptiveCondensationTracker.h
 *
 *  Created on: 20.09.2012
 *      Author: poschmann
 */

#ifndef ADAPTIVECONDENSATIONTRACKER_H_
#define ADAPTIVECONDENSATIONTRACKER_H_

#include "tracking/Sample.h"
#include "opencv2/core/core.hpp"
#include "boost/optional.hpp"
#include <memory>
#include <vector>

using std::shared_ptr;
using boost::optional;
using cv::Mat;
using std::vector;

namespace tracking {

class Rectangle;
class Sampler;
class MeasurementModel;
class AdaptiveMeasurementModel;
class PositionExtractor;

/**
 * Condensation tracker that adapts to the appearance of the tracked object over time.
 */
class AdaptiveCondensationTracker {
public:

	/**
	 * Constructs a new adaptive condensation tracker.
	 *
	 * @param[in] sampler The sampler.
	 * @param[in] initialMeasurementModel The initial static measurement model.
	 * @param[in] measurementModel The adaptive measurement model.
	 * @param[in] extractor The position extractor.
	 */
	explicit AdaptiveCondensationTracker(shared_ptr<Sampler> sampler,
			shared_ptr<MeasurementModel> initialMeasurementModel, shared_ptr<AdaptiveMeasurementModel> measurementModel,
			shared_ptr<PositionExtractor> extractor);

	~AdaptiveCondensationTracker();

	/**
	 * Processes the next image and returns the most probable object position.
	 *
	 * @param[in] image The next image.
	 * @return The bounding box around the most probable object position if there is an object.
	 */
	optional<Rectangle> process(const Mat& image);

	/**
	 * @return The current samples.
	 */
	inline const vector<Sample>& getSamples() const {
		return samples;
	}

	/**
	 * @return The sampler.
	 */
	inline shared_ptr<Sampler> getSampler() {
		return sampler;
	}

	/**
	 * @param[in] sampler The new sampler.
	 */
	inline void setSampler(shared_ptr<Sampler> sampler) {
		this->sampler = sampler;
	}

	/**
	 * @return True if the adaptive measurement model should be used, false otherwise.
	 */
	inline bool isUsingAdaptiveModel() {
		return useAdaptiveModel;
	}

	/**
	 * @param[in] active Flag that indicates whether the adaptive measurement model should be used.
	 */
	void setUseAdaptiveModel(bool useAdaptive);

	/**
	 * @return True if the adaptive measurement model was used, false otherwise.
	 */
	inline bool wasUsingAdaptiveModel() {
		return usedAdaptiveModel;
	}

private:

	vector<Sample> samples;    ///< The current samples.
	vector<Sample> oldSamples; ///< The previous samples.

	optional<Sample> oldPosition; ///< The previous position.
	vector<double> offset;        ///< The movement of the tracked object's center of the previous time step.
	bool useAdaptiveModel;        ///< Flag that indicates whether the adaptive measurement model should be used.
	bool usedAdaptiveModel;       ///< Flag that indicates whether the adaptive measurement model was used.

	shared_ptr<Sampler> sampler;                           ///< The sampler.
	shared_ptr<MeasurementModel> initialMeasurementModel;  ///< The initial static measurement model.
	shared_ptr<AdaptiveMeasurementModel> measurementModel; ///< The adaptive measurement model.
	shared_ptr<PositionExtractor> extractor;               ///< The position extractor.
};

} /* namespace tracking */
#endif /* ADAPTIVECONDENSATIONTRACKER_H_ */
