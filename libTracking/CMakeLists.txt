SET( SUBPROJECT_NAME Tracking ) # my own variable, not cmake's
PROJECT( ${SUBPROJECT_NAME} )
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET( ${SUBPROJECT_NAME}_VERSION_MAJOR 0 )
SET( ${SUBPROJECT_NAME}_VERSION_MINOR 1 )

# find dependencies
FIND_PACKAGE(Boost REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED core)

# source and header files
SET(HEADERS
	include/svm.h
	include/tracking/ApproximateSigmoidParameterComputation.h
	include/tracking/ChangableDetectorSvm.h
	include/tracking/CondensationTracker.h
	include/tracking/DensityPositionExtractor.h
	include/tracking/DualSvmModel.h
	include/tracking/ExactSigmoidParameterComputation.h
	include/tracking/FilteringPositionExtractor.h
	include/tracking/FrameBasedSvmTraining.h
	include/tracking/GridSampler.h
	include/tracking/LowVarianceSampling.h
	include/tracking/MaxWeightPositionExtractor.h
	include/tracking/MeasurementModel.h
	include/tracking/PositionExtractor.h
	include/tracking/Rectangle.h
	include/tracking/ResamplingAlgorithm.h
	include/tracking/ResamplingSampler.h
	include/tracking/Sample.h
	include/tracking/Sampler.h
	include/tracking/SelfLearningWvmOeSvmModel.h
	include/tracking/SigmoidParameterComputation.h
	include/tracking/SimpleTransitionModel.h
	include/tracking/SvmTraining.h
	include/tracking/TransitionModel.h
	include/tracking/UnchangingSigmoidParameterComputation.h
	include/tracking/WeightedMeanPositionExtractor.h
	include/tracking/WvmOeSvmModel.h
)
SET(SOURCE
	src/svm.cpp
	src/tracking/ApproximateSigmoidParameterComputation.cpp
	src/tracking/ChangableDetectorSvm.cpp
	src/tracking/CondensationTracker.cpp
	src/tracking/DensityPositionExtractor.cpp
	src/tracking/DualSvmModel.cpp
	src/tracking/ExactSigmoidParameterComputation.cpp
	src/tracking/FilteringPositionExtractor.cpp
	src/tracking/FrameBasedSvmTraining.cpp
	src/tracking/GridSampler.cpp
	src/tracking/LowVarianceSampling.cpp
	src/tracking/MaxWeightPositionExtractor.cpp
	src/tracking/Rectangle.cpp
	src/tracking/ResamplingSampler.cpp
	src/tracking/Sample.cpp
	src/tracking/SelfLearningWvmOeSvmModel.cpp
	src/tracking/SigmoidParameterComputation.cpp
	src/tracking/SimpleTransitionModel.cpp
	src/tracking/UnchangingSigmoidParameterComputation.cpp
	src/tracking/WeightedMeanPositionExtractor.cpp
	src/tracking/WvmOeSvmModel.cpp
)

include_directories( "include" )

# add dependencies
include_directories( ${libFeatureDetection_SOURCE_DIR} )

# make library
add_library( ${SUBPROJECT_NAME} SHARED ${SOURCE} ${HEADERS} )
