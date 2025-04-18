#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

#include "System/window.hpp"
#include "Games/games.hpp"
#include "System/settings.hpp"
#include "defines.hpp"

#include <sstream>


int main(int argc, char* argv[])
{
    #if defined __APPLE__
	static char path[1024]="";

	if (strlen(path)==0)
    {
		// Determining the Resources path inside the .app bundle
		CFBundleRef mainBundle = CFBundleGetMainBundle();
		CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL( mainBundle );
		if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, sizeof(path)))
			fprintf(stderr, "Unable to determine data path.");
		CFRelease(resourcesURL);
		chdir(path);
	}
    #endif

	// Parse command line options
    for (int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "-help" || std::string(argv[i]) == "--help")
        {
            std::cout << "Usage:               mars [Options]"                                                                          << std::endl;
            std::cout << "Basic Options:"                                                                                               << std::endl;
            std::cout << "    -cfg  <Path>     Sets the absolute path to the configuration directory of the game."                      << std::endl;
            std::cout << "    -data <Path>     Sets the absolute path to the data directory of the game,"                               << std::endl;
            std::cout << "                     which contains the folders sound/, tex/ and so on."                                      << std::endl;
            std::cout                                                                                                                   << std::endl;
            std::cout << "Miscellaneous Options:"                                                                                       << std::endl;
            std::cout << "    -help            Print program options."                                                                  << std::endl;
            std::cout << "    -version         Print program version."                                                                  << std::endl;
            return 0;
        }
        else if (std::string(argv[i]) == "-v" || std::string(argv[i]) == "-version" || std::string(argv[i]) == "--version" )
        {
            std::cout << "M.A.R.S. - a ridiculous shooter " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << " (C) 2010-2011 by Felix Lauer and Simon Schneegans.\n";
            return 0;
        }
        else if (std::string(argv[i]) == "-cfg")
        {
            if (++i < argc)
                settings::sConfigPath = argv[i];
            else
                std::cout << "Option \"-cfg\" expects a path to be provided following it.\n";
        }
        else if (std::string(argv[i]) == "-data")
        {
            if (++i < argc)
                settings::sDataPath = argv[i];
            else
                std::cout << "Option \"-data\" expects a path to be provided following it.\n";
        }
        else
            std::cout << "Unknown option \"" << argv[i] << "\". Use -help for a complete list of supported flags.\n";
    }

    // start the game
    if (window::open())
    {
        games:: start(games::gMenu);

        if (settings::bLogoSigns)
            std::cout << "Happy Gaming..." << std::endl;

        window::mainLoop();
    }
    return 0;
}
