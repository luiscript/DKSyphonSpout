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

#include "ofMain.h"
#include "DKModule.hpp"

#ifdef TARGET_OSX
#include "ofxSyphon.h"
#endif

#ifdef _WIN32
#include "ofxSpout2Receiver.h"
#endif

class DKTextureClient : public DKModule {
private:

#ifdef TARGET_OSX
	ofxSyphonClient syphonClient;
	ofxSyphonServerDirectory serverDirectory;
	vector<ofxSyphonServerDescription> serversList;
#endif
#ifdef _WIN32
	ofxSpout2::Receiver spoutReceiver;
#endif 
	ofFbo* fbo;
	bool drawFbo = false;
	int serverIndex;
	vector<string> serverOptions;
	int alpha;
public:
	void setup();
	void update();
	void draw();
	void addModuleParameters();
#ifdef TARGET_OSX
	void serverAnnounced(ofxSyphonServerDirectoryEventArgs& arg);
	//void serverRetired(ofxSyphonServerDirectoryEventArgs& args);
#endif
	void onServerSelected(ofxDatGuiDropdownEvent e);
	void updateDropDownOptions();

	ofFbo* getFbo();
	void unMount();
};
