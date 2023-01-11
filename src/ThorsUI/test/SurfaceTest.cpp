#include "gtest/gtest.h"
#include "test/MockSDL.h"
#include "Surface.h"
#include <fstream>

TEST(SurfaceTest, SurfaceCreate)
{

    auto action = []()
    {
        ThorsAnvil::UI::Surface         surface;
    };

    EXPECT_NO_THROW(
        action();
    );
}

TEST(SurfaceTest, SurfaceCreateMove)
{
    auto action = []()
    {
        ThorsAnvil::UI::Surface         surface1;
        ThorsAnvil::UI::Surface         surface2(std::move(surface1));
    };

    EXPECT_NO_THROW(
        action();
    );
}

TEST(SurfaceTest, SurfaceAssignMove)
{
    auto action = []()
    {
        ThorsAnvil::UI::Surface         surface1;
        ThorsAnvil::UI::Surface         surface2;

        surface1 = std::move(surface1);
    };

    EXPECT_NO_THROW(
        action();
    );
}

TEST(SurfaceTest, SurfaceLoadFromFile)
{
    auto action = []()
    {
        std::ifstream   input("test/data/Apple.jpg");
        ThorsAnvil::UI::Surface         surface;
        input >> surface;

        ASSERT_TRUE(input.eof());
    };

    EXPECT_NO_THROW(
        action();
    );
}

TEST(SurfaceTest, SurfaceSaveToFileJPG)
{
    auto action = []()
    {
        std::ifstream   input("test/data/Apple.jpg");
        ThorsAnvil::UI::Surface         surface;
        input >> surface;

        std::ofstream   output("/tmp/test.jpg");
        output << ThorsAnvil::UI::SurfaceToJPG(surface);

        ASSERT_TRUE(output.good());
    };

    EXPECT_NO_THROW(
        action();
    );
}

TEST(SurfaceTest, SurfaceSaveToFilePNG)
{
    auto action = []()
    {
        std::ifstream   input("test/data/Apple.jpg");
        ThorsAnvil::UI::Surface         surface;
        input >> surface;

        std::ofstream   output("/tmp/test.png");
        output << ThorsAnvil::UI::SurfaceToPNG(surface);

        ASSERT_TRUE(output.good());
    };

    EXPECT_NO_THROW(
        action();
    );
}
