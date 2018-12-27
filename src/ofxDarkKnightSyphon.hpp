/*
 Copyright (C) 2018 Luis Fernando García [http://luiscript.com]
 
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

#ifndef ofxDarkKnightSyphon_hpp
#define ofxDarkKnightSyphon_hpp

#include "ofMain.h"
#include "module.hpp"

#ifdef TARGET_OSX
#include "ofxSyphon.h"
#endif

class ofxDarkKnightSyphon : public Module
{
private:
    #ifdef TARGET_OSX
    ofxSyphonServer syphonOut;
    #endif
    ofFbo * fbo;
    bool drawFbo = false;
    string serverName;
public:
    void setup();
    void update();
    void draw();
    void setFbo(ofFbo *);
    void addModuleParameters();
    ofFbo * getFbo();
    void onTextInputEvent(ofxDatGuiTextInputEvent);
};

class DarkKnightSyphonClient : public Module{
private:
    ofxSyphonClient syphonClient;
    ofxSyphonServerDirectory serverDirectory;
    ofFbo * fbo;
    bool drawFbo = false;
    int serverIndex;
    vector<ofxSyphonServerDescription> serversList;
    vector<string> serverOptions;
    int alpha;
public:
    void setup();
    void update();
    void draw();
    void addModuleParameters();
    
    void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
    void serverRetired(ofxSyphonServerDirectoryEventArgs &args);
    
    void onServerSelected(ofxDatGuiDropdownEvent e);
    void updateDropDownOptions();
    
    ofFbo * getFbo();
};

#endif /* ofxDarkKnightSyphon_hpp */
