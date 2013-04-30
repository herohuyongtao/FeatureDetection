/*
 * DidLandmarkFormatParser.cpp
 *
 *  Created on: 28.04.2013
 *      Author: Patrik Huber
 */

#include "imageio/DidLandmarkFormatParser.hpp"
#include "imageio/Landmark.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string.hpp"
#include <stdexcept>
#include <utility>
#include <fstream>

using std::copy;
using std::sort;
using std::runtime_error;
using std::make_pair;
using boost::algorithm::trim;
using boost::algorithm::starts_with;
using std::ifstream;
using std::stringstream;

namespace imageio {

DidLandmarkFormatParser::~DidLandmarkFormatParser() {}

const LandmarkCollection DidLandmarkFormatParser::read(vector<string> landmarkData)
{
	LandmarkCollection lmcoll;
	for (auto line : landmarkData) {
		// TODO: Add checking of #, //, ... (see readFromDidFile(...) below).
		lmcoll.insert(readFromDidLine(line));	// the landmark is also converted to .tlms format here!
	}
	return lmcoll;
}

LandmarkCollection DidLandmarkFormatParser::readFromDidFile(const string& filename) {
	ifstream ifLM(filename);
	string strLine;
	LandmarkCollection listLM;

	while(getline(ifLM, strLine))
	{
		boost::algorithm::trim(strLine);
		// allow comments
		if ( !strLine.empty() && !starts_with(strLine, "#") && !starts_with(strLine, "//") )
		{
			Landmark lm = readFromDidLine(strLine);
			listLM.insert(lm);
		}
	}
	return listLM;
}

Landmark DidLandmarkFormatParser::readFromDidLine(const string& line) {
	stringstream sstrLine(line);
	string name;
	Vec3f fPos(0.0f, 0.0f, 0.0f);
	float fVertexNumber;

	if ( !(sstrLine >> fPos[0] >> fPos[1] >> fVertexNumber) ) {
		throw std::runtime_error("Landmark parsing format error, use .did");
	}
	fPos[2] = 0;
	int vertexNumber = boost::lexical_cast<int>(fVertexNumber);
	name = didToTlmsName(vertexNumber);
	return Landmark(name, fPos, cv::Size2f(), true);
}

string DidLandmarkFormatParser::didToTlmsName(int didVertexId) {
	if (didLmMapping.empty()) {
		didLmMapping.insert(make_pair( 177, "right.eye.corner_outer"));
		didLmMapping.insert(make_pair( 610, "left.eye.corner_outer"));
		didLmMapping.insert(make_pair( 114, "center.nose.tip"));
		//didLmMapping.insert(make_pair(  35, "center.chin.tip"));	// I think the .did Chin-tip is about 1cm farther up
		didLmMapping.insert(make_pair( 181, "right.eye.corner_inner"));
		didLmMapping.insert(make_pair(1125, "right.eye.top"));	// Should check that in model
		didLmMapping.insert(make_pair(1180, "right.eye.bottom"));
		didLmMapping.insert(make_pair( 614, "left.eye.corner_inner"));
		didLmMapping.insert(make_pair(2368, "left.eye.top"));
		didLmMapping.insert(make_pair(2425, "left.eye.bottom"));
		//didLmMapping.insert(make_pair( 438, ""));
		didLmMapping.insert(make_pair( 398, "right.lips.corner"));
		didLmMapping.insert(make_pair( 812, "left.lips.corner"));
		didLmMapping.insert(make_pair( 329, "center.lips.upper.outer"));
		didLmMapping.insert(make_pair( 423, "center.lips.upper.inner"));
		didLmMapping.insert(make_pair( 442, "center.lips.lower.inner"));
		didLmMapping.insert(make_pair( 411, "center.lips.lower.outer"));
		didLmMapping.insert(make_pair( 225, "right.eyebrow.bend.lower"));
		didLmMapping.insert(make_pair( 157, "right.eyebrow.inner_lower"));
		//didLmMapping.insert(make_pair( 233, ""));
		//didLmMapping.insert(make_pair(  79, "")); // Some nose-LM, look up in gravis pics
		didLmMapping.insert(make_pair( 658, "left.eyebrow.bend.lower"));
		didLmMapping.insert(make_pair( 590, "left.eyebrow.inner_lower"));
		//didLmMapping.insert(make_pair( 666, ""));
		//didLmMapping.insert(make_pair( 516, "")); // Some nose-LM, look up in gravis pics
		//didLmMapping.insert(make_pair( 332, ""));
		//didLmMapping.insert(make_pair( 295, ""));
		//didLmMapping.insert(make_pair( 379, ""));
		//didLmMapping.insert(make_pair( 270, "")); // Maybe center.nose.attachement_to_philtrum?
		//didLmMapping.insert(make_pair( 440, ""));
		//didLmMapping.insert(make_pair( 314, ""));
		//didLmMapping.insert(make_pair( 416, ""));
		//didLmMapping.insert(make_pair( 404, ""));
		//didLmMapping.insert(make_pair( 263, ""));
		//didLmMapping.insert(make_pair( 735, ""));
		//didLmMapping.insert(make_pair( 828, ""));
		//didLmMapping.insert(make_pair( 817, ""));
		//didLmMapping.insert(make_pair( 692, ""));
		//didLmMapping.insert(make_pair( 359, "")); // Right ear-jaw junction (...)
		//didLmMapping.insert(make_pair( 776, "")); // Left ear-jaw junction (...)
	}
	return didLmMapping.at(didVertexId); // Todo: Use [] instead of at? Error-checking?
}


} /* namespace imageio */