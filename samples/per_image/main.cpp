#include <cvcmd/application.hpp>

#include <iostream>

class application : public cvcmd::application
{
public:
	application() :
		cvcmd::application()
	{
		display_image(true);
		opt1_description("Text to write on image.");
	}

	virtual std::string description()
	{
		return
			"this is libcvcmd sample program. display images and quit."
			;
	}

	virtual int on_image(const cv::Mat& image)
	{
		cv::Mat display_image(image);

		cv::putText(
			display_image, opts()[0], {10,70}, cv::FONT_HERSHEY_SIMPLEX, 2, {0,0,255});

		add_display_image("image", display_image);
		return 0;
	}
};

int main(int argc, char* argv[])
{
	return application().exec(argc, argv);
}

