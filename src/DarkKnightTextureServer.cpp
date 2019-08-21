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

#include "DarkKnightTextureServer.h"

void DarkKnightTextureServer::setup()
{
	fbo = nullptr;
	serverName = "output";
	addInputConnection(ConnectionType::DK_FBO);
	addOutputConnection(ConnectionType::DK_FBO);

#ifdef _WIN64
	//spoutSender.init(serverName);
	//spoutSender.
#endif
}

void DarkKnightTextureServer::update()
{

}

void DarkKnightTextureServer::draw()
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

void DarkKnightTextureServer::setFbo(ofFbo* fboPtr)
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

ofFbo* DarkKnightTextureServer::getFbo()
{
	return fbo;
}

void DarkKnightTextureServer::addModuleParameters()
{
	gui->onTextInputEvent(this, &DarkKnightTextureServer::onTextInputEvent);
	gui->addTextInput("Server name", "output");
}

void DarkKnightTextureServer::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
	serverName = e.target->getText();
}

void DarkKnightTextureServer::unMount()
{
#ifdef _WIN32
	spoutSender.exit();
#endif

}