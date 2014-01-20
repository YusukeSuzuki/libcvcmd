#include "cvcmd/application.hpp"

#include <opencv2/highgui/highgui.hpp>

#include <boost/program_options.hpp>

#include <iostream>

namespace cvcmd
{

class application::implementation
{
public:
	implementation() :
		process_per_image_(true),
		display_image_(false),
		display_images_(),
		output_images_()
	{
	}

	virtual ~implementation() noexcept
	{
	}

public:
	bool process_per_image_;
	bool display_image_;

	std::map<std::string, cv::Mat> display_images_;
	std::map<std::string, cv::Mat> output_images_;
};

application::application() :
	implementation_( std::make_shared<implementation>() )
{
}

application::~application() noexcept
{
}

int application::exec(int argc, char* argv[])
{
	std::vector<cv::Mat> images;

	// program options
	namespace po = boost::program_options;

	po::options_description options("options");

	options.add_options()
		("help,h", "print this message.")
		("without-display",
		 "suppress displaying image with window")
		("input-file",
			po::value<std::vector<std::string>>()->default_value(
				std::vector<std::string>({}),""),
			"input files")
		;
	
	po::positional_options_description hidden;
	hidden.add("input-file", -1);

	po::variables_map vm;
	po::store(
		po::command_line_parser(argc, argv).options(options).allow_unregistered().
		positional(hidden).run(), vm);

	po::notify(vm);

	if( vm.count("help") > 0 )
	{
		std::cout << description() << std::endl;
		std::cout << options << std::endl;
		return 0;
	}

	bool display = !(vm.count("without-display") > 0);

	// read images
	auto filenames = vm["input-file"].as<std::vector<std::string>>();

	if(filenames.empty())
	{
		std::cout << "no input file" << std::endl;
		return 0;
	}

	// lambda functions
	auto per_image = [this](
		const std::vector<std::string>& filenames, bool display)
	{
		for(const auto& filename : filenames)
		{
			cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);

			if( int ret = on_image(image) ) return ret;

			if(does_display_image() && display)
			{
				for(const auto& named_image : implementation_->display_images_)
				{
					cv::imshow(named_image.first, named_image.second);
				}

				cv::waitKey(0);
				cv::destroyAllWindows();
			}

			implementation_->display_images_.clear();

			for(const auto& named_image : implementation_->output_images_)
			{
				cv::imwrite(named_image.first, named_image.second);
			}
		}

		return 0;
	};

	auto whole_images = [this](const std::vector<cv::Mat>& images)
	{
		if( int ret = on_images(images) ) return ret;

		return 0;
	};

	// do image processing
	if( does_process_per_image() )
	{
		return per_image(filenames, display);
	}

	return whole_images(images);
}

bool application::does_process_per_image()
{
	return implementation_->process_per_image_;
}

bool application::process_per_image(bool which)
{
	return implementation_->process_per_image_ = which;
}

bool application::does_display_image()
{
	return implementation_->display_image_;
}

bool application::display_image(bool which)
{
	return implementation_->display_image_ = which;
}

void application::add_output_image(const std::string& name, const cv::Mat& image)
{
	implementation_->output_images_[name] = image;
}

void application::add_display_image(const std::string& name, const cv::Mat& image)
{
	implementation_->display_images_[name] = image;
}

/**
 * virtual functions
 */
//@{
int application::on_image(const cv::Mat& image)
{
	return 0;
}

int application::on_images(const std::vector<cv::Mat>& images)
{
	return 0;
}

void application::pre_exec(int argc, char* argv[])
{
}

std::string application::description()
{
	return "this is libcvcmd application base class. do nothing.";
}
//@}

}

