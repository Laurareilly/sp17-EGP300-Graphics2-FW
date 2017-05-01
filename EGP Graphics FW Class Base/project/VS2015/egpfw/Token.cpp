#include "Token.h"
#include <string>
#include <fstream>

void TokenParser::parseTokens()
{
}

void TokenParser::printTokens()
{
}

void EOFToken::printToken()
{
	cout << "Token [EOF]" << endl;
}

int EOFToken::parseToken(fstream & aStream, int aInputCharacter)
{
}

void EOLToken::printToken()
{
	cout << "Token [EOL]" << endl;
}

int EOLToken::parseToken(fstream & aStream, int aInputCharacter)
{
}

void NumberLiteralToken::printToken()
{
	cout << "Token [literal: " << mNumberLiteralString << " ]" << endl;
}

//append each character to the literal string until closing quotations
int NumberLiteralToken::parseToken(fstream & aStream, int aInputCharacter)
{
	mNumberLiteralString.clear();
	while (true)
	{
		aInputCharacter = aStream.get();
		if (aInputCharacter == '\\')
		{
			aInputCharacter = aStream.peek();
			if (aInputCharacter == '\"' || aInputCharacter == '\\')
			{
				mNumberLiteralString += '\\';
				aInputCharacter = aStream.get();
				mNumberLiteralString += aInputCharacter;
				continue;
			}
			if (aInputCharacter == 0x0A)
			{
				cout << "Error: EOL encounted before closing literal quotes" << endl;
				exit(0);
			}
			if (aInputCharacter == -1)
			{
				cout << "Error: EOF encounted before closing literal quotes" << endl;
				exit(0);
			}
			mNumberLiteralString += aInputCharacter;
			continue;
		}
		if (aInputCharacter != '\"' && aInputCharacter != -1)
		{
			mNumberLiteralString += aInputCharacter;
			continue;
		}

		if (aInputCharacter == -1)
		{
			cout << "Error: EOF encounted before closing literal quotes" << endl;
			exit(0);
		}
		aInputCharacter = aStream.get();
		return aInputCharacter;
	}
}

void PunctuationToken::printToken()
{
	cout << "Token [punctuation: " << mPunctuationString << " ]" << endl;
}

int PunctuationToken::parseToken(fstream & aStream, int aInputCharacter)
{
	mPunctuationString = aInputCharacter;
	switch (aInputCharacter)
	{
	case '!':
		break;
	case '#':
		break;
	case '%':
		break;
	case '*':
		break;
	case '+':
		break;
	case '-':
		break;
	case '.':
		break;
	case '/':
		break;
	case '=':
		break;
	case '<':
		break;
	case '>':
		break;
	case '|':
		break;
	default:
		break;
	}

	aInputCharacter = aStream.get();
	return aInputCharacter;
}

void WhitespaceToken::printToken()
{
	cout << "Token [whitespace]" << endl;
}

int WhitespaceToken::parseToken(fstream & aStream, int aInputCharacter)
{
}

void SymbolToken::printToken()
{
	cout << "Token [symbol: " << mSymbol << " ]" << endl;
}

//symbol is any group of characters that begin with a character ranging A-Z (lower or uppercase) or an underscore
int SymbolToken::parseToken(fstream & aStream, int aInputCharacter)
{
	mSymbol = aInputCharacter;
	while (true)
	{
		aInputCharacter = aStream.get();
		if (isalpha(aInputCharacter) || isdigit(aInputCharacter) || aInputCharacter == '_')
		{
			mSymbol += aInputCharacter;
			continue;
		}
		return aInputCharacter;
	}
}

void InvalidToken::printToken()
{
	cout << "Token [invalid: " << mInvalidCharacter << " ]" << endl;
}

int InvalidToken::parseToken(fstream & aStream, int aInputCharacter)
{
}
