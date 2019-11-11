/*
 Copyright (C) 2019 Luis Fernando García [http://luiscript.com]

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

#include "DKTextureClient.h"

void DKTextureClient::setup()
{
	alpha = 255;
	fbo = nullptr;
	drawFbo = false;
#ifdef TARGET_OSX
	serverDirectory.setup();
	syphonClient.setup();
	ofAddListener(serverDirectory.events.serverAnnounced, this, &DKTextureClient::serverAnnounced);
	// ofAddListener(serverDirectory.events.serverRetired, this, &DarkKnightSyphonClient::serverRetired);
	serversList = serverDirectory.getServerList();

	for (auto server : serversList)
	{
		string option = server.serverName + ":" + server.appName;
		serverOptions.push_back(option);
	}
#endif
#ifdef _WIN32
	string option = "SHOW SPOUT SENDERS";
	serverOptions.push_back(option);
	//spoutReceiver.init();
	spoutReceiver.setup();
#endif

	fbo = new ofFbo;
	fbo->allocate(getModuleWidth(), getModuleHeight(), GL_RGBA, 4);
	fbo->begin();
	ofClear(0, 0, 0, 0);
	fbo->end();

	updateDropDownOptions();

	addOutputConnection(DKConnectionType::DK_FBO);
}

void DKTextureClient::update()
{

}

void DKTextureClient::draw()
{
	if (drawFbo)
	{

#ifdef TARGET_OSX
		fbo->begin();
		syphonClient.draw(0, 0);
		fbo->end();
#endif
#ifdef _WIN32
		spoutReceiver.updateTexture();
		fbo->begin();
		ofClear(0, 0, 0, 0);
		spoutReceiver.getTexture().draw(0, 0);
		ofPushStyle();
		ofSetColor(0, 0, 0, 255 - alpha);
		ofFill();
		ofDrawRectangle(0, 0, getModuleWidth(), getModuleHeight());
		ofPopStyle();
		fbo->end();
#endif
	}
}


ofFbo* DKTextureClient::getFbo()
{
	return fbo;
}

void DKTextureClient::addModuleParameters()
{

	gui->addDropdown("Select server", serverOptions)->onDropdownEvent(this, &DKTextureClient::onServerSelected)
		;
	gui->addSlider("Alpha", 0, 255)->bind(alpha);
}

void DKTextureClient::onServerSelected(ofxDatGuiDropdownEvent e)
{
	serverIndex = e.child;
	drawFbo = true;
#ifdef TARGET_OSX
	syphonClient.set(serverDirectory.getDescription(serverIndex));
#endif
#ifdef _WIN32
	//spoutReceiver.selectSenderPanel();
	spoutReceiver.showSenders();
#endif
	
}

#ifdef TARGET_OSX
void DKTextureClient::serverAnnounced(ofxSyphonServerDirectoryEventArgs& arg)
{

	for (auto& dir : arg.servers)
	{
		string option = dir.serverName + ":" + dir.appName;
		serverOptions.push_back(option);
	}

	updateDropDownOptions();
}
#endif

void DKTextureClient::updateDropDownOptions()
{
	vector<ofxDatGuiComponent*> items = gui->getItems();
	int x = 0;
	for (auto item : items)
	{
		if (ofToLower(item->getName()) == "select server")
		{
			items.erase(items.begin() + x);
		}
		x++;
	}

	gui->setItems(items);
	gui->addDropdown("Select server", serverOptions)->onDropdownEvent(this, &DKTextureClient::onServerSelected);
	gui->setWidth(moduleGuiWidth);
}

void DKTextureClient::unMount()
{
#ifdef _WIN32
	//spoutReceiver.exit();
	spoutReceiver.exit();
#endif
}
