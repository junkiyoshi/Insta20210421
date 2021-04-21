#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(300, 4);
	this->triangle_list = ico_sphere.getMesh().getUniqueFaces();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	this->line.clear();
	this->yolk.clear();

	for (auto& triangle : this->triangle_list) {

		glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;

		if (ofNoise(glm::vec4(avg * 0.005, ofGetFrameNum() * 0.008)) < 0.5) {

			this->mesh.addVertex(triangle.getVertex(0));
			this->mesh.addVertex(triangle.getVertex(1));
			this->mesh.addVertex(triangle.getVertex(2));

			this->mesh.addColor(ofColor(239));
			this->mesh.addColor(ofColor(239));
			this->mesh.addColor(ofColor(239));

			this->line.addVertex(triangle.getVertex(0));
			this->line.addVertex(triangle.getVertex(1));
			this->line.addVertex(triangle.getVertex(2));

			this->line.addColor(ofColor(39));
			this->line.addColor(ofColor(39));
			this->line.addColor(ofColor(39));

			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3);
			this->line.addTriangle(this->line.getNumVertices() - 1, this->line.getNumVertices() - 2, this->line.getNumVertices() - 3);

		}

		for (int i = 0; i < 3; i++) {

			auto noise_value = ofNoise(glm::vec4(triangle.getVertex(i) * 0.005, ofGetFrameNum() * 0.005));
			auto noise_radius = ofMap(noise_value, 0, 1, 100, 250);

			this->yolk.addVertex(glm::normalize(triangle.getVertex(i)) * noise_radius);
			this->yolk.addColor(ofColor(244, 192, 39));
		}

		this->yolk.addTriangle(this->yolk.getNumVertices() - 1, this->yolk.getNumVertices() - 2, this->yolk.getNumVertices() - 3);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.37);
	ofRotateY(ofGetFrameNum() * 0.72);

	this->mesh.draw();
	this->line.drawWireframe();

	this->yolk.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}