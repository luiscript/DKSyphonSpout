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

#include "ofxDarkKnightSyphon.hpp"


void ofxDarkKnightSyphon::setup()
{
    fbo = nullptr;
    serverName = "output";
}

void ofxDarkKnightSyphon::update()
{
    
}

void ofxDarkKnightSyphon::draw()
{
    if(drawFbo)
    {
        #ifdef TARGET_OSX
        syphonOut.publishTexture(&fbo->getTexture());
        #endif
    }
    
}

void ofxDarkKnightSyphon::setFbo(ofFbo * fboPtr)
{
    fbo  = fboPtr;
    drawFbo = fboPtr != nullptr;
    if(drawFbo)
    {
        #ifdef TARGET_OSX
        syphonOut.setName(serverName);
        #endif
    }
}

ofFbo * ofxDarkKnightSyphon::getFbo()
{
    return fbo;
}


void ofxDarkKnightSyphon::drawMasterOutput()
{
    drawOutputConnection();
}

void ofxDarkKnightSyphon::drawMasterInput()
{
    drawInputConnection();
}

void ofxDarkKnightSyphon::addModuleParameters()
{
    gui->onTextInputEvent(this, &ofxDarkKnightSyphon::onTextInputEvent);
    gui->addTextInput("Server name", "output");
}

void ofxDarkKnightSyphon::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    serverName = e.target->getText();
}




void DarkKnightSyphonClient::setup()
{
    alpha = 255;
    fbo = nullptr;
    drawFbo = false;
    serverDirectory.setup();
    syphonClient.setup();
    
    ofAddListener(serverDirectory.events.serverAnnounced, this, &DarkKnightSyphonClient::serverAnnounced);
    // ofAddListener(serverDirectory.events.serverRetired, this, &DarkKnightSyphonClient::serverRetired);
    
    fbo = new ofFbo;
    fbo->allocate(getModuleWidth(), getModuleHeight(), GL_RGB32F_ARB);
    fbo->begin();
    ofClear(0, 0, 0, 0);
    fbo->end();
    
    serversList = serverDirectory.getServerList();
    
    for (auto server : serversList)
    {
        string option = server.serverName + ":" + server.appName;
        serverOptions.push_back(option);
    }
    
    updateDropDownOptions();
}

void DarkKnightSyphonClient::update()
{
    
}

void DarkKnightSyphonClient::draw()
{
    if(drawFbo)
    {
        fbo->begin();
        syphonClient.draw(0, 0);
        
        ofPushStyle();
        ofSetColor(0, 0, 0, 255 - alpha);
        ofFill();
        ofDrawRectangle(0, 0, getModuleWidth(), getModuleHeight());
        ofPopStyle();
        
        fbo->end();
    }
    
}


ofFbo * DarkKnightSyphonClient::getFbo()
{
    return fbo;
}


void DarkKnightSyphonClient::drawMasterOutput()
{
    drawOutputConnection();
}

void DarkKnightSyphonClient::drawMasterInput()
{
    
}

void DarkKnightSyphonClient::addModuleParameters()
{
    
    gui->addDropdown("Select syphon server", serverOptions)->onDropdownEvent(this, &DarkKnightSyphonClient::onServerSelected)
    ;
    gui->addSlider("Alpha", 0, 255)->bind(alpha);
}

void DarkKnightSyphonClient::onServerSelected(ofxDatGuiDropdownEvent e)
{
    serverIndex = e.child;
    syphonClient.set(serverDirectory.getDescription(serverIndex));
    drawFbo = true;
}

void DarkKnightSyphonClient::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg)
{
    
    for (auto & dir : arg.servers)
    {
        string option = dir.serverName + ":" + dir.appName;
        serverOptions.push_back(option);
    }
    
    updateDropDownOptions();
}

void DarkKnightSyphonClient::updateDropDownOptions()
{
    vector<ofxDatGuiComponent*> items = gui->getItems();
    int x = 0;
    for (auto item : items)
    {
        if(ofToLower(item->getName()) == "select syphon server")
        {
            items.erase(items.begin() + x);
        }
        x++;
    }
    
    gui->setItems(items);
    gui->addDropdown("Select syphon server", serverOptions)->onDropdownEvent(this, &DarkKnightSyphonClient::onServerSelected);
    
    gui->setTheme(this->getGuiTheme());
    gui->setWidth(450);
}
