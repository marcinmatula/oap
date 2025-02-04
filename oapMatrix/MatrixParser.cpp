#include "MatrixParser.h"
#include <algorithm>

namespace matrixUtils
{

Parser::Parser() : m_text("")
{}

Parser::Parser(const std::string& text) : m_text(text)
{}

Parser::Parser(const Parser& parser) : m_text(parser.m_text)
{}

Parser::~Parser()
{}

void Parser::setText(const std::string& text)
{ m_text = text; }

bool Parser::getColumns(uintt& columns) const
{
  uintt value = 0;
  bool status = getValue(value, ID_COLUMNS);
  columns = value;
  return status;
}

bool Parser::getRows(uintt& rows) const
{
  uintt value = 0;
  bool status = getValue(value, ID_ROWS);
  rows = value;
  return status;
}

bool Parser::getValue(uintt& value, const std::string& id) const
{
  size_t pos = m_text.find(id, 0);
  if (pos == std::string::npos)
  {
    return false;
  }
  pos += id.length() + 1;
  if (pos >= m_text.length())
  {
    return false;
  }
  size_t pos1 = m_text.find_first_not_of("-0123456789", pos);
  value = atoi(m_text.substr(pos, pos1 - pos).c_str());
  return true;
}

bool Parser::satof(floatt& output, const std::string& str) const
{
  if (str.find_first_not_of(".-0123456789e") != std::string::npos)
  {
    return false;
  }
  floatt value = 1;
  int index = 0;
  if (str[0] == '-')
  {
    value = -1;
    index = 1;
  }
  const char* cs = str.c_str();
  output = value * atof(cs + index);
  return true;
}

bool Parser::getArrayStr(std::string& array, unsigned int which) const
{
  debugAssert(which > 0);
  size_t pos = 0;
  pos = m_text.find("[", pos);
  for (int fa = 0; fa < which - 1; ++fa)
  {
    pos = m_text.find("[", pos + 1);
  }
  if (pos == std::string::npos)
  {
    return false;
  }
  size_t pos1 = m_text.find("]", pos);
  if (pos1 == std::string::npos)
  {
    return false;
  }
  ++pos;
  array = m_text.substr(pos, pos1 - pos);
  return true;
}

bool Parser::getArray(std::vector<floatt>& array,
                      const std::string& arrayStr) const
                      {
  size_t pos = 0;
  size_t pos1 = std::string::npos;
  do
  {
    pos1 = arrayStr.find_first_of(",|", pos);
    std::string elementStr = arrayStr.substr(pos, pos1 - pos);
    std::string::iterator it = std::remove_if(
        elementStr.begin(), elementStr.end(), (int (*)(int))std::isspace);
    elementStr.erase(it, elementStr.end());
    if (parseElement(array, elementStr) == false)
    {
      return false;
    }
    pos = pos1 + 1;
  } while (pos1 != std::string::npos);
  return true;
}

bool Parser::parseElement(std::vector<floatt>& array,
                          const std::string& elementStr) const
                          {
  if (isOneElement(elementStr))
  {
    return parseFloatElement(array, elementStr);
  } else
  {
    return parseFloatsElement(array, elementStr);
  }
}

bool Parser::isOneElement(const std::string& elementStr) const
{
  return elementStr.find("<") == std::string::npos &&
         elementStr.find(">") == std::string::npos;
}

bool Parser::parseFloatElement(std::vector<floatt>& array,
                               const std::string& elementStr) const
                               {
  floatt v = 0;
  bool status = satof(v, elementStr.c_str());
  if (status)
  {
    array.push_back(v);
  }
  return status;
}

bool Parser::parseFloatsElement(std::vector<floatt>& array,
                                const std::string& elementStr) const
                                {
  size_t pos = elementStr.find("<");
  size_t pos1 = elementStr.find(">");
  if (pos1 != elementStr.size() - 1)
  {
    return false;
  }
  std::string partStr = elementStr.substr(pos, pos1 - pos);
  size_t posDigit1 = partStr.find_first_of(".-0123456789");
  size_t posDigit2 = partStr.find_first_not_of(".-0123456789", posDigit1);
  int count = atoi(partStr.substr(posDigit1, posDigit2 - posDigit1).c_str());
  std::string sub = elementStr.substr(0, pos);
  floatt value;
  bool status = satof(value, sub.c_str());
  if (status)
  {
    for (int fa = 0; fa < count; ++fa)
    {
      array.push_back(value);
    }
  }
  return status;
}

bool Parser::parseArray(unsigned int which)
{
  std::string arrayStr;
  if (getArrayStr(arrayStr, which) == false)
  {
    return false;
  }
  m_array.clear();
  if (getArray(m_array, arrayStr) == false)
  {
    return false;
  }
  return true;
}

floatt Parser::getValue(uintt index) const
{ return m_array.at(index); }

size_t Parser::getLength() const
{ return m_array.size(); }

const floatt* Parser::getData() const
{ return m_array.data(); }

std::pair<floatt*, size_t> CreateArray(const std::string& text, unsigned int which)
{
  Parser parser(text);
  if (parser.parseArray(which) == false)
  {
    return std::make_pair<floatt*, size_t>(NULL, 0);
  }
  size_t length = parser.getLength();
  floatt* array = new floatt[length];
  memcpy(array, parser.getData(), length * sizeof(floatt));
  return std::make_pair/*<floatt*, size_t>*/(array, length);
}

}
