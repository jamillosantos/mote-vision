/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 17, 2016
 */

#include <gtest/gtest.h>
#include <imgprocs/framebufferiterator.h>

GTEST_TEST(imgprocs_frame_buffer_iterator_rgb24, inBounds)
{
	uint8_t image[25 * 3];
	mote::data::Pixel px;
	mote::imgprocs::FramBufferIteratorRGB24 it(image, 5, 5, 1);

	ASSERT_TRUE(it.inBounds(0, 0));
	ASSERT_TRUE(it.inBounds(4, 0));
	ASSERT_TRUE(it.inBounds(0, 4));
	ASSERT_TRUE(it.inBounds(4, 4));
	ASSERT_FALSE(it.inBounds(5, 0));
	ASSERT_FALSE(it.inBounds(0, 5));
	ASSERT_FALSE(it.inBounds(5, 5));
}

GTEST_TEST(imgprocs_frame_buffer_iterator_rgb24, getPixel_success)
{
	uint8_t image[25 * 3];
	for (unsigned int i = 0; i < sizeof(image); i++)
		image[i] = i;

	mote::data::Pixel px;
	mote::imgprocs::FramBufferIteratorRGB24 it(image, 5, 5, 1);

	ASSERT_TRUE(it.getPixel(px, 0, 0));
	ASSERT_EQ(0, px.b);
	ASSERT_EQ(1, px.g);
	ASSERT_EQ(2, px.r);

	ASSERT_TRUE(it.getPixel(px, 1, 0));
	ASSERT_EQ(3, px.b);
	ASSERT_EQ(4, px.g);
	ASSERT_EQ(5, px.r);

	ASSERT_TRUE(it.getPixel(px, 1, 1));
	ASSERT_EQ(18, px.b);
	ASSERT_EQ(19, px.g);
	ASSERT_EQ(20, px.r);

	ASSERT_TRUE(it.getPixel(px, 4, 4));
	ASSERT_EQ(72, px.b);
	ASSERT_EQ(73, px.g);
	ASSERT_EQ(74, px.r);
}

GTEST_TEST(imgprocs_frame_buffer_iterator_rgb24, getPixel_error)
{
	uint8_t image[25 * 3];
	for (unsigned int i = 0; i < sizeof(image); i++)
		image[i] = i;

	mote::data::Pixel px;
	px.b = 250;
	px.g = 251;
	px.r = 252;
	mote::imgprocs::FramBufferIteratorRGB24 it(image, 5, 5, 1);

	ASSERT_FALSE(it.getPixel(px, 5, 0));
	// Ensure that the pixel reference was not changed.
	ASSERT_EQ(250, px.b);
	ASSERT_EQ(251, px.g);
	ASSERT_EQ(252, px.r);

	ASSERT_FALSE(it.getPixel(px, 0, 5));
	// Ensure that the pixel reference was not changed.
	ASSERT_EQ(250, px.b);
	ASSERT_EQ(251, px.g);
	ASSERT_EQ(252, px.r);

	ASSERT_FALSE(it.getPixel(px, 5, 5));
	// Ensure that the pixel reference was not changed.
	ASSERT_EQ(250, px.b);
	ASSERT_EQ(251, px.g);
	ASSERT_EQ(252, px.r);
}

GTEST_TEST(imgprocs_frame_buffer_iterator_rgb24, getAddress)
{
	uint8_t image[25 * 3];
	for (unsigned int i = 0; i < sizeof(image); i++)
		image[i] = i;

	mote::imgprocs::FramBufferIteratorRGB24 it(image, 5, 5, 1);

	uint8_t *addr;

	addr = it.getAddress(0, 0);
	ASSERT_EQ(image, addr);

	addr = it.getAddress(1, 1);
	ASSERT_EQ(image + 6*3, addr);
}

GTEST_TEST(imgprocs_frame_buffer_iterator_rgb24, get_and_go)
{
	uint8_t image[25 * 3];
	for (unsigned int i = 0; i < sizeof(image); i++)
		image[i] = i;

	mote::data::Pixel px;
	mote::imgprocs::FramBufferIteratorRGB24 it(image, 5, 5, 1);


	ASSERT_TRUE(it.go(0, 0));
	it.get(px);
	ASSERT_EQ(0, px.b);
	ASSERT_EQ(1, px.g);
	ASSERT_EQ(2, px.r);

	ASSERT_TRUE(it.go(1, 0));
	it.get(px);
	ASSERT_EQ(3, px.b);
	ASSERT_EQ(4, px.g);
	ASSERT_EQ(5, px.r);

	ASSERT_TRUE(it.go(1, 1));
	it.get(px);
	ASSERT_EQ(18, px.b);
	ASSERT_EQ(19, px.g);
	ASSERT_EQ(20, px.r);

	ASSERT_TRUE(it.go(4, 4));
	it.get(px);
	ASSERT_EQ(72, px.b);
	ASSERT_EQ(73, px.g);
	ASSERT_EQ(74, px.r);
}

GTEST_TEST(imgprocs_frame_buffer_iterator_rgb24, goNext)
{
	uint8_t image[25 * 3];
	for (unsigned int i = 0; i < sizeof(image); i++)
		image[i] = i;

	mote::data::Pixel px;
	mote::imgprocs::FramBufferIteratorRGB24 it(image, 5, 5, 1);

	unsigned int count = 0;
	while (it.goNext())
	{
		++count;
	}
	ASSERT_EQ(25, count);
}

GTEST_TEST(imgprocs_frame_buffer_iterator_rgb24, goDirections)
{
	uint8_t image[25 * 3];
	for (unsigned int i = 0; i < sizeof(image); i++)
		image[i] = i;

	mote::data::Pixel px;
	mote::imgprocs::FramBufferIteratorRGB24 it(image, 5, 5, 1);

	it.go(0, 0);
	it.get(px);
	ASSERT_EQ(0, px.b);
	ASSERT_EQ(1, px.g);
	ASSERT_EQ(2, px.r);

	ASSERT_TRUE(it.goLeft());
	it.get(px);
	ASSERT_EQ(3, px.b);
	ASSERT_EQ(4, px.g);
	ASSERT_EQ(5, px.r);

	ASSERT_TRUE(it.goRight());
	it.get(px);
	ASSERT_EQ(0, px.b);
	ASSERT_EQ(1, px.g);
	ASSERT_EQ(2, px.r);

	ASSERT_TRUE(it.goDown());
	it.get(px);
	ASSERT_EQ(15, px.b);
	ASSERT_EQ(16, px.g);
	ASSERT_EQ(17, px.r);

	ASSERT_TRUE(it.goUp());
	it.get(px);
	ASSERT_EQ(0, px.b);
	ASSERT_EQ(1, px.g);
	ASSERT_EQ(2, px.r);

	ASSERT_TRUE(it.goDown(4));
	ASSERT_TRUE(it.goLeft(4));
	it.get(px);
	ASSERT_EQ(72, px.b);
	ASSERT_EQ(73, px.g);
	ASSERT_EQ(74, px.r);


	ASSERT_TRUE(it.goUp(4));
	ASSERT_TRUE(it.goRight(4));
	it.get(px);
	ASSERT_EQ(0, px.b);
	ASSERT_EQ(1, px.g);
	ASSERT_EQ(2, px.r);
}

GTEST_TEST(imgprocs_frame_buffer_iterator_rgb24, setPixel)
{
	uint8_t image[25 * 3];
	for (unsigned int i = 0; i < sizeof(image); i++)
		image[i] = i;

	mote::data::Pixel px;
	mote::imgprocs::FramBufferIteratorRGB24 it(image, 5, 5, 1);

	// gets the (4, 4) pixel just for checking.
	it.getPixel(px, 4, 4);
	ASSERT_EQ(72, px.b);
	ASSERT_EQ(73, px.g);
	ASSERT_EQ(74, px.r);

	// gets the (0, 0) pixel and check it.
	it.getPixel(px, 0, 0);
	ASSERT_EQ(0, px.b);
	ASSERT_EQ(1, px.g);
	ASSERT_EQ(2, px.r);

	// Sets the (0, 0) pixel value into (4, 4) pixel and checks it.
	it.setPixel(4, 4, px);
	ASSERT_TRUE(it.getPixel(px, 4, 4));
	ASSERT_EQ(0, px.b);
	ASSERT_EQ(1, px.g);
	ASSERT_EQ(2, px.r);
}