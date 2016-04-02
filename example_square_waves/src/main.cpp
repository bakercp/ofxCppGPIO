#include "ofApp.h"
#include "ofAppNoWindow.h"


int main()
{
    ofAppNoWindow window;
	ofSetupOpenGL(&window, 0, 0, OF_WINDOW);
    ofRunApp(std::make_shared<ofApp>());
}
