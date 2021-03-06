#ifndef TOMATO_SYNTAX_TREE_HPP
#define TOMATO_SYNTAX_TREE_HPP


#include <string>
#include <memory>
#include <vector>

#include "visitor.hpp"
#include "operators.hpp"


#define ACCEPT_VISITOR void accept(Visitor &visitor) override { visitor.process(*this); }


namespace Tomato::Syntax
{
    /**
     * @brief Abstract syntax tree abstract node.
     */
    struct ASTNode
    {
        virtual void accept(class Visitor &visitor) = 0;
    };

    struct Statement : ASTNode {};
    struct Expression : Statement {};

    struct Identifier : Expression
    {
        explicit Identifier(
                const std::string &name
        );

        std::string name;

        ACCEPT_VISITOR
    };

    struct Literal : Expression
    {
        enum class Type { Integer, Float, Boolean, Character, String };
        Literal(Type type, const std::string &lexeme);

        Type type;
        std::string lexeme;

        ACCEPT_VISITOR
    };

    struct BinaryOperation : Expression
    {
        BinaryOperation(
                std::shared_ptr<Expression> left,
                BinaryOperator              operation,
                std::shared_ptr<Expression> right
        );

        std::shared_ptr<Expression> left;
        BinaryOperator              operation;
        std::shared_ptr<Expression> right;

        ACCEPT_VISITOR
    };

    struct UnaryOperation : Expression
    {
        UnaryOperation(
                UnaryOperator               operation,
                std::shared_ptr<Expression> operand
        );

        UnaryOperator               operation;
        std::shared_ptr<Expression> operand;

        ACCEPT_VISITOR
    };

    struct Indexation : Expression
    {
        Indexation(
                std::shared_ptr<Expression> array,
                std::shared_ptr<Expression> index
        );

        std::shared_ptr<Expression> array;
        std::shared_ptr<Expression> index;

//        ACCEPT_VISITOR
    };

    struct MemberAccess : Expression
    {
        MemberAccess(
                std::shared_ptr<Expression> expression,
                std::shared_ptr<Identifier> member
        );

        std::shared_ptr<Expression> expression;
        std::shared_ptr<Identifier> member;

//        ACCEPT_VISITOR
    };

    struct StatementBlock : ASTNode
    {
        StatementBlock() = default;
        explicit StatementBlock(
                std::vector<std::shared_ptr<Statement>> statements
        );

        std::vector<std::shared_ptr<Statement>> statements;

        ACCEPT_VISITOR
    };

    struct ValueDeclaration : Statement
    {
        ValueDeclaration(
                std::shared_ptr<Identifier> value,
                std::shared_ptr<Identifier> type,
                std::shared_ptr<Expression> init,
                bool constant
        );

        std::shared_ptr<Identifier> value;
        std::shared_ptr<Identifier> type;
        std::shared_ptr<Expression> init;
        bool constant;

        ACCEPT_VISITOR
    };

    struct Assignment : Statement
    {
        Assignment(
                std::shared_ptr<Expression> destination,
                std::shared_ptr<Expression> source
        );

        std::shared_ptr<Expression> destination;
        std::shared_ptr<Expression> source;

        ACCEPT_VISITOR
    };

    struct ConditionalStatement : Statement
    {
        ConditionalStatement(
                std::shared_ptr<Expression>      condition,
                std::shared_ptr<StatementBlock>  then_case,
                std::shared_ptr<StatementBlock>  else_case
        );

        std::shared_ptr<Expression>      condition;
        std::shared_ptr<StatementBlock>  then_case;
        std::shared_ptr<StatementBlock>  else_case;

        ACCEPT_VISITOR
    };

    struct ConditionalLoop : Statement
    {
        ConditionalLoop(
                std::shared_ptr<Expression> condition,
                std::shared_ptr<StatementBlock> body
        );

        std::shared_ptr<Expression> condition;
        std::shared_ptr<StatementBlock> body;

        ACCEPT_VISITOR
    };

    struct PrintStatement : Statement
    {
        explicit PrintStatement(
                std::shared_ptr<Expression> expression
        );

        std::shared_ptr<Expression> expression;

        ACCEPT_VISITOR
    };

    struct ReadStatement : Statement
    {
        explicit ReadStatement(
                std::shared_ptr<Expression> expression
        );

        std::shared_ptr<Expression> expression;

        ACCEPT_VISITOR
    };

    struct Program : ASTNode
    {
        std::vector<std::shared_ptr<Statement>> statements;

        ACCEPT_VISITOR
    };

    struct Function : Statement
    {
        struct Argument
        {
            std::shared_ptr<Identifier> param;
            std::shared_ptr<Identifier> type;
        };

        Function(
                std::shared_ptr<Identifier> identifier,
                const std::vector<Argument> &arguments,
                std::shared_ptr<Identifier> return_type,
                std::shared_ptr<StatementBlock> body
        );

        std::shared_ptr<Identifier> identifier;
        std::vector<Argument> arguments;
        std::shared_ptr<Identifier> return_type;
        std::shared_ptr<StatementBlock> body;

        ACCEPT_VISITOR
    };

    struct ReturnStatement : Statement
    {
        explicit ReturnStatement(std::shared_ptr<Expression> expression);

        std::shared_ptr<Expression> expression;

        ACCEPT_VISITOR
    };

    struct Call : Expression
    {
        Call(
                std::shared_ptr<Identifier> function,
                const std::vector<std::shared_ptr<Expression>> &arguments
        );

        std::shared_ptr<Identifier> function;
        std::vector<std::shared_ptr<Expression>> arguments;

        ACCEPT_VISITOR
    };
}


#endif //TOMATO_SYNTAX_TREE_HPP
