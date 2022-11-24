#include "gtest/gtest.h"
#include "Util.h"

TEST(UtilTest, ColorCompareEqual)
{
    EXPECT_TRUE(ThorsAnvil::UI::C::blue == ThorsAnvil::UI::C::blue);
}

TEST(UtilTest, ColorCompareNotEqual)
{
    EXPECT_TRUE(ThorsAnvil::UI::C::blue != ThorsAnvil::UI::C::red);
}

TEST(UtilTest, ColorCompareEqualDynamic)
{
    ThorsAnvil::UI::Color   localBlue{0, 0, 255, 255};
    EXPECT_TRUE(ThorsAnvil::UI::C::blue == localBlue);
}

TEST(UtilTest, RectContainsHit)
{
    ThorsAnvil::UI::Rect    rect{100, 100, 200, 200};
    EXPECT_TRUE(rect.contains({200, 200}));
}

TEST(UtilTest, RectContainsMissAbove)
{
    ThorsAnvil::UI::Rect    rect{100, 100, 200, 200};
    EXPECT_FALSE(rect.contains({200, 50}));
}

TEST(UtilTest, RectContainsMissBelow)
{
    ThorsAnvil::UI::Rect    rect{100, 100, 200, 200};
    EXPECT_FALSE(rect.contains({200, 350}));
}

TEST(UtilTest, RectContainsMissLeft)
{
    ThorsAnvil::UI::Rect    rect{100, 100, 200, 200};
    EXPECT_FALSE(rect.contains({50, 200}));
}

TEST(UtilTest, RectContainsMissRight)
{
    ThorsAnvil::UI::Rect    rect{100, 100, 200, 200};
    EXPECT_FALSE(rect.contains({350, 200}));
}

TEST(UtilTest, RectIntersectionAll)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_TRUE(rectBig.intersect({120, 120, 20, 20}));
}

TEST(UtilTest, RectIntersectionTopLeft)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_TRUE(rectBig.intersect({80, 80, 40, 40}));
}

TEST(UtilTest, RectIntersectionTopInner)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_TRUE(rectBig.intersect({120, 80, 160, 40}));
}

TEST(UtilTest, RectIntersectionTopOuter)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_TRUE(rectBig.intersect({80, 80, 240, 40}));
}

TEST(UtilTest, RectIntersectionTopRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_TRUE(rectBig.intersect({280, 80, 40, 40}));
}

TEST(UtilTest, RectIntersectionRightInner)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_TRUE(rectBig.intersect({280, 120, 40, 160}));
}

TEST(UtilTest, RectIntersectionRightOuter)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_TRUE(rectBig.intersect({280, 80, 40, 240}));
}

TEST(UtilTest, RectIntersectionBotRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_TRUE(rectBig.intersect({280, 280, 40, 40}));
}

TEST(UtilTest, RectIntersectionBotInner)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_TRUE(rectBig.intersect({120, 280, 160, 40}));
}

TEST(UtilTest, RectIntersectionBotOuter)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_TRUE(rectBig.intersect({80, 280, 240, 40}));
}

TEST(UtilTest, RectIntersectionBotLeft)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_TRUE(rectBig.intersect({80, 280, 40, 40}));
}

TEST(UtilTest, RectIntersectionLeftInner)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_TRUE(rectBig.intersect({80, 120, 40, 160}));
}

TEST(UtilTest, RectIntersectionLeftOuter)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_TRUE(rectBig.intersect({80, 80, 40, 240}));
}

TEST(UtilTest, RectIntersectionAboveTopLeft)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({80, 80, 40, 15}));
}

TEST(UtilTest, RectIntersectionAboveTopInner)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({120, 80, 160, 15}));
}

TEST(UtilTest, RectIntersectionAboveTopOuter)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({80, 80, 240, 15}));
}

TEST(UtilTest, RectIntersectionAboveTopRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({280, 80, 40, 15}));
}

TEST(UtilTest, RectIntersectionRightTopRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({305, 80, 15, 40}));
}

TEST(UtilTest, RectIntersectionRightRightInner)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({305, 120, 15, 160}));
}

TEST(UtilTest, RectIntersectionRightRightOuter)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({305, 80, 15, 240}));
}

TEST(UtilTest, RectIntersectionRightBotRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({305, 280, 15, 40}));
}

TEST(UtilTest, RectIntersectionBelowBotRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({280, 305, 40, 15}));
}

TEST(UtilTest, RectIntersectionBelowBotInner)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({120, 305, 160, 15}));
}

TEST(UtilTest, RectIntersectionBelowBotOuter)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({80, 305, 240, 15}));
}

TEST(UtilTest, RectIntersectionBelowBotLeft)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({80, 305, 40, 15}));
}

TEST(UtilTest, RectIntersectionLeftBotLeft)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({80, 280, 15, 40}));
}

TEST(UtilTest, RectIntersectionLeftLeftInner)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({80, 120, 15, 160}));
}

TEST(UtilTest, RectIntersectionLeftLeftOuter)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({80, 80, 15, 240}));
}

TEST(UtilTest, RectIntersectionLeftTopRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_FALSE(rectBig.intersect({80, 80, 15, 240}));
}

TEST(UtilTest, RectCollisionAll)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({120, 120}, {20, 20}));
}

TEST(UtilTest, RectCollisionTopLeft)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::TopLeft, rectBig.collision({80, 80}, {40, 40}));
}

TEST(UtilTest, RectCollisionTop)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Top, rectBig.collision({120, 80}, {160, 40}));
}

TEST(UtilTest, RectCollisionTopRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::TopRight, rectBig.collision({320, 80}, {-40, 40}));
}

TEST(UtilTest, RectCollisionRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Right, rectBig.collision({320, 120}, {-40, 160}));
}

TEST(UtilTest, RectCollisionBotRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::BotRight, rectBig.collision({319, 319}, {-40, -40}));
}

TEST(UtilTest, RectCollisionBot)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Bot, rectBig.collision({120, 320}, {160, -40}));
}

TEST(UtilTest, RectCollisionBotLeft)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::BotLeft, rectBig.collision({80, 320}, {40, -40}));
}

TEST(UtilTest, RectCollisionLeft)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Left, rectBig.collision({80, 120}, {40, 160}));
}

TEST(UtilTest, RectCollisionAboveTopLeft)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({80, 80}, {40, 15}));
}

TEST(UtilTest, RectCollisionAboveTopInner)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({120, 80}, {160, 15}));
}

TEST(UtilTest, RectCollisionAboveTopOuter)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({80, 80}, {240, 15}));
}

TEST(UtilTest, RectCollisionAboveTopRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({280, 80}, {40, 15}));
}

TEST(UtilTest, RectCollisionRightTopRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({305, 80}, {15, 40}));
}

TEST(UtilTest, RectCollisionRightRightInner)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({305, 120}, {15, 160}));
}

TEST(UtilTest, RectCollisionRightRightOuter)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({305, 80}, {15, 240}));
}

TEST(UtilTest, RectCollisionRightBotRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({305, 280}, {15, 40}));
}

TEST(UtilTest, RectCollisionBelowBotRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({280, 305}, {40, 15}));
}

TEST(UtilTest, RectCollisionBelowBotInner)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({120, 305}, {160, 15}));
}

TEST(UtilTest, RectCollisionBelowBotOuter)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({80, 305}, {240, 15}));
}

TEST(UtilTest, RectCollisionBelowBotLeft)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({80, 305}, {40, 15}));
}

TEST(UtilTest, RectCollisionLeftBotLeft)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({80, 280}, {15, 40}));
}

TEST(UtilTest, RectCollisionLeftLeftInner)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({80, 120}, {15, 160}));
}

TEST(UtilTest, RectCollisionLeftLeftOuter)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({80, 80}, {15, 240}));
}

TEST(UtilTest, RectCollisionLeftTopRight)
{
    ThorsAnvil::UI::Rect    rectBig{100, 100, 200, 200};
    EXPECT_EQ(ThorsAnvil::UI::Miss, rectBig.collision({80, 80}, {15, 240}));
}


