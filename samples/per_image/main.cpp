#include <cvcmd/application.hpp>

#include <iostream>

class application : public cvcmd::application
{
public:
	application()
	{
		display_image(true);
	}

	virtual std::string description()
	{
		return
			"this is libcvcmd sample program. display images and quit."
			;
	}

	virtual int on_image(const cv::Mat& image)
	{
		add_display_image("image", image);
		return 0;
	}
};

int main(int argc, char* argv[])
{
	return application().exec(argc, argv);
}

