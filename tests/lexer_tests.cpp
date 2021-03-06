#include <gtest/gtest.h>
#include <syntax/lexer.hpp>


TEST(LexerTest, GeneralTest)
{
    using namespace Tomato::Syntax;

    Lexer lexer;

    lexer.set_text("let pi = 3.1415926");

    ASSERT_EQ(lexer.get_next().terminal, Terminal::Let);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::Identifier);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::Operator);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::FloatLiteral);

    ASSERT_TRUE(lexer.eof());

    ASSERT_EQ(lexer.get_next().terminal, Terminal::EndOfFile);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::EndOfFile);

    ASSERT_TRUE(lexer.eof());
}


TEST(LexerTest, Terminals)
{
    using namespace Tomato::Syntax;

    Lexer lexer;

    lexer.set_text("let var import if then else end while do for in func");

    ASSERT_EQ(lexer.get_next().terminal, Terminal::Let);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::Var);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::Import);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::If);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::Then);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::Else);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::End);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::While);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::Do);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::For);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::In);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::Func);

    lexer.set_text("+  -  *  /  %  ^  =  <  >  "
                           "+= -= *= /= %= ^= == <= >= != "
                           "and or not");

    for (int i = 0; i < 22; ++i)
    {
        ASSERT_EQ(lexer.get_next().terminal, Terminal::Operator);
    }

    ASSERT_TRUE(lexer.eof());

    lexer.set_text("read print true false");

    ASSERT_EQ(lexer.get_next().terminal, Terminal::Read);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::Print);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::BooleanLiteral);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::BooleanLiteral);

    ASSERT_TRUE(lexer.eof());

    lexer.set_text("([{}])");

    ASSERT_EQ(lexer.get_next().terminal, Terminal::LParen);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::LSquareBracket);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::LCurlyBracket);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::RCurlyBracket);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::RSquareBracket);
    ASSERT_EQ(lexer.get_next().terminal, Terminal::RParen);

    ASSERT_TRUE(lexer.eof());
}
