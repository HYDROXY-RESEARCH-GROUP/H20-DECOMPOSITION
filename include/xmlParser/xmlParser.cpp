#include "XmlParser.h"
//=============================================================================
//== Function Name  :   XmlParser::exists
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== fileName   const std::string   The name of the file that is in use
//==
//== Description
//== --------------------------------------------------------------------------
//== This function is used to check if the XML file exists
//=============================================================================
bool XmlParser::exists(const std::string fileName)
{
    std::fstream checkFile(fileName);
    return checkFile.is_open();
}
//=============================================================================
//== Function Name  :   XmlParser::open
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== strFile    const std::string   The name of the file that the user passes
//==                                in the code
//==
//== Description
//== --------------------------------------------------------------------------
//== This function is used to open the XML file, first checking to see if it
//== exists first
//=============================================================================
bool XmlParser::open(const std::string strFile)
{

    if (exists(strFile))
    {
        std::cout << "Error: File alread exists.\n";
        return false;
    }

    outFile.open(strFile);
    if (outFile.is_open())
    {
        std::cout << "File created successfully.\n";
        outFile << "<!--XML Document-->\n";
        outFile << "<?xml version='1.0' encoding='us-ascii'>\n";
        indent = 0;
        openTags = 0;
        openElements = 0;
        return true;
    }

    return false;
}
//=============================================================================
//== Function Name  :   XmlParser::close
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== N/a        N/a                 N/a
//==
//== Description
//== --------------------------------------------------------------------------
//== This function is used to close the XML file
//=============================================================================
void XmlParser::close()
{
    if (outFile.is_open())
    {
        outFile.close();
    }
    else
    {
        std::cout << "File already closed.\n";
    }
}
//=============================================================================
//== Function Name  :   XmlParser::writeOpenTag
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== openTag    const std::string   The name of the tag being created
//==
//== Description
//== --------------------------------------------------------------------------
//== This function creates a new tag, checking that the file is open, and saves
//== the tag name in a vector to keep track of it
//=============================================================================
void XmlParser::writeOpenTag(const std::string openTag)
{
    if (outFile.is_open())
    {
        for (int i = 0; i < indent; i++)
        {
            outFile << "\t";
        }
        tempOpenTag.resize(openTags + 1);
        outFile << "<" << openTag << ">\n";
        tempOpenTag[openTags] = openTag;
        indent += 1;
        openTags += 1;
    }
    else
    {
        std::cout << "File is closed. Unable to write to file.\n";
    }
}
//=============================================================================
//== Function Name  :   XmlParser::writeCloseTag
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== N/a        N/a                 N/a
//==
//== Description
//== --------------------------------------------------------------------------
//== This function closes the currently open tag
//=============================================================================
void XmlParser::writeCloseTag()
{
    if (outFile.is_open())
    {
        indent -= 1;
        for (int i = 0; i < indent; i++)
        {
            outFile << "\t";
        }
        outFile << "</" << tempOpenTag[openTags - 1] << ">\n";
        tempOpenTag.resize(openTags - 1);
        openTags -= 1;
    }
    else
    {
        std::cout << "File is closed. Unable to write to file.\n";
    }
}
//=============================================================================
//== Function Name  :   XmlParser::writeStartElementTag
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== elementTag const std::string   The name of the element being created
//==
//== Description
//== --------------------------------------------------------------------------
//== This function creates a new element tag and saves the name to a vector
//=============================================================================
void XmlParser::writeStartElementTag(const std::string elementTag)
{
    if (outFile.is_open())
    {
        for (int i = 0; i < indent; i++)
        {
            outFile << "\t";
        }
        tempElementTag.resize(openElements + 1);
        tempElementTag[openElements] = elementTag;
        openElements += 1;
        outFile << "<" << elementTag;
    }
    else
    {
        std::cout << "File is closed. Unable to write to file.\n";
    }
}
//=============================================================================
//== Function Name  :   XmlParser::writeEndElementTag
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== N/a        N/a                 N/a
//==
//== Description
//== --------------------------------------------------------------------------
//== This function closed the currently opened element tag
//=============================================================================
void XmlParser::writeEndElementTag()
{
    if (outFile.is_open())
    {
        outFile << "</" << tempElementTag[openElements - 1] << ">\n";
        tempElementTag.resize(openElements - 1);
        openElements -= 1;
    }
    else
    {
        std::cout << "File is closed. Unable to write to file.\n";
    }
}
//=============================================================================
//== Function Name  :   XmlParser::writeAttribute
//==
//== Perameters
//== Name           Type                Description
//== ----------     -----------         --------------------
//== outAttribute   const std::string   The attribute being written out
//==
//== Description
//== --------------------------------------------------------------------------
//== This function writes an attribute (if any) after the element tag is first
//== opened and before the output for the element is written
//=============================================================================
void XmlParser::writeAttribute(const std::string outAttribute)
{
    if (outFile.is_open())
    {
        outFile << " " << outAttribute;
    }
    else
    {
        std::cout << "File is closed. Unable to write to file.\n";
    }
}
//=============================================================================
//== Function Name  :   XmlParser::writeString
//==
//== Perameters
//== Name           Type                Description
//== ----------     -----------         --------------------
//== writeString    const std::string   The string to be written to the element
//==
//== Description
//== --------------------------------------------------------------------------
//=============================================================================
void XmlParser::writeString(const std::string outString)
{
    if (outFile.is_open())
    {
        outFile << ">" << outString;
    }
    else
    {
        std::cout << "File is closed. Unable to write to file.\n";
    }
}