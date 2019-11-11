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

#include "DKTextureServer.h"

void DKTextureServer::setup()
{
	fbo = nullptr;
	serverName = "output";
	addInputConnection(DKConnectionType::DK_FBO);
	addOutputConnection(DKConnectionType::DK_FBO);

#ifdef _WIN64
	//spoutSender.init(serverName);
	//spoutSender.
#endif
}

void DKTextureServer::update()
{

}

void DKTextureServer::draw()
{
	if (drawFbo)
	{
		#ifdef TARGET_OSX
			syphonOut.publishTexture(&fbo->getTexture());
		#endif
		#ifdef _WIN32
			//spoutSender.send(fbo->getTexture());
			spoutSender.sendTexture(fbo->getTexture(), serverName);
		#endif
	}

}

void DKTextureServer::setFbo(ofFbo* fboPtr)
{
	fbo = fboPtr;
	drawFbo = fboPtr != nullptr;
	if (drawFbo)
	{
	#ifdef TARGET_OSX
		syphonOut.setName(serverName);
	#endif
	}
}

ofFbo* DKTextureServer::getFbo()
{
	return fbo;
}

void DKTextureServer::addModuleParameters()
{
	gui->onTextInputEvent(this, &DKTextureServer::onTextInputEvent);
	gui->addTextInput("Server name", "output");
}

void DKTextureServer::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
	serverName = e.target->getText();
}

void DKTextureServer::unMount()
{
#ifdef _WIN32
	spoutSender.exit();
#endif

}
