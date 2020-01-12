/*
 Copyright (C) 2019 Luis Fernando Garc’a PŽrez [http://luiscript.com]

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef DKTextureServer_hpp
#define DKTextureServer_hpp

#include "ofMain.h"
#include "DKModule.hpp"

#ifdef TARGET_OSX
#include "ofxSyphon.h"
#endif

#ifdef _WIN32
#include "ofxSpout2Sender.h"
#endif


class DKTextureServer : public DKModule
{
private:
#ifdef TARGET_OSX
	ofxSyphonServer syphonOut;
#endif

#ifdef _WIN32
	ofxSpout2::Sender spoutSender;
#endif

	ofFbo* fbo;
	bool drawFbo = false;
	string serverName;
public:
	void setup();
	void update();
	void draw();
	void setFbo(ofFbo*);
	void addModuleParameters();
	ofFbo* getFbo();
	void onTextInputEvent(ofxDatGuiTextInputEvent);
	void unMount();
};

#endif /* DKTextureServer_hpp */
