#ifndef LIB_CVCMD_APPLICATION_HPP__
#define LIB_CVCMD_APPLICATION_HPP__

#include <opencv2/core/core.hpp>

#include <memory>
#include <string>

namespace cvcmd
{

class application
{
public:
	/**
	 * constructor
	 */
	application();

	/**
	 * destructor
	 */
	virtual ~application() noexcept;

	/**
	 */
	int exec(int argc, char* argv[]);
	
	/**
	 * default true
	 */
	bool does_process_per_image();
	bool process_per_image(bool which);

	/**
	 * default false
	 */
	bool does_display_image();
	bool display_image(bool which);

	/**
	 */
	void add_output_image(const std::string& name, const cv::Mat& image);
	void add_display_image(const std::string& name, const cv::Mat& image);

	/**
	 */
	virtual int on_image(const cv::Mat& image);
	virtual int on_images(const std::vector<cv::Mat>& images);

	virtual void pre_exec(int argc, char* argv[]);

	virtual std::string description();

private:
	class implementation;
	std::shared_ptr<implementation> implementation_;
	friend implementation;
};

}

#endif
