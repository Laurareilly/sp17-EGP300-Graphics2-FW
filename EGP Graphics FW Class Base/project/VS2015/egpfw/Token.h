#pragma once

//followed this tutorial by Martyn Rae http://www.dreamincode.net/forums/topic/153718-fundamentals-of-parsing/

#include "iostream"
#include <vector>
using namespace std;

//a base token class that all tokens in our enum can derive from
class Token
{
public:

	enum TokenType
	{
		Invalid, 
		Symbol,
		Whitespace,
		Punctuation,
		NumberLiteral,
		EndOfLine,
		EndOfFile
	};

	Token(TokenType aType) { mTokenType = aType; }
	virtual ~Token() {};

	virtual void printToken() = 0;
	virtual int parseToken(fstream& aStream, int aInputCharacter) = 0;

	TokenType getType() { return mTokenType; }

private:

	TokenType mTokenType;
};

class InvalidToken : public Token
{
public:

	InvalidToken() : Token(Symbol) {};
	~InvalidToken() {};

	void printToken() override;
	int parseToken(fstream& aStream, int aInputCharacter) override;
private:
	int mInvalidCharacter;
};

class SymbolToken : public Token
{
public:

	SymbolToken() : Token(Symbol) {};
	~SymbolToken() {};

	void printToken() override;
	int parseToken(fstream& aStream, int aInputCharacter) override;
private:
	string mSymbol;
};

class WhitespaceToken : public Token
{
public:

	WhitespaceToken() : Token(Whitespace) {};
	~WhitespaceToken() {};

	void printToken() override;
	int parseToken(fstream& aStream, int aInputCharacter) override;
};

class PunctuationToken : public Token
{
public:

	PunctuationToken() : Token(Punctuation) {};
	~PunctuationToken() {};

	void printToken() override;
	int parseToken(fstream& aStream, int aInputCharacter) override;

private:
	string mPunctuationString;
};

class NumberLiteralToken : public Token
{
public:

	NumberLiteralToken() : Token(NumberLiteral) {};
	~NumberLiteralToken() {};

	void printToken() override;
	int parseToken(fstream& aStream, int aInputCharacter) override;

private:
	string mNumberLiteralString;
};

class EOLToken : public Token
{
public:

	EOLToken() : Token(EndOfLine) {};
	~EOLToken() {};

	void printToken() override;
	int parseToken(fstream& aStream, int aInputCharacter) override;
};

class EOFToken : public Token
{
public:

	EOFToken() : Token(EndOfFile) {};
	~EOFToken() {};

	void printToken() override;
	int parseToken(fstream& aStream, int aInputCharacter) override;
};

//identify tokens based off of their leading character, creates the correct token and calls it's parse function
class TokenParser
{
public:
	TokenParser(fstream& aStream) : stream(aStream) {};
	~TokenParser() {};

	void parseTokens();
	void printTokens();

private:
	fstream& stream;
	vector<Token*> mTokens;
};