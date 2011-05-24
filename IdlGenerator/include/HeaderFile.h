/*-------------------------------------------------------------
 Copyright (C)| 
 File: HeaderFile.h
 Author: Zephyr Shannon
 Date: 2010-3-2 10:31:50
 Version: 
 Description: 一个文件
 Others: 
 Function List: 
 Histroy: 
 -------------------------------------------------------------*/

#ifndef __ZEPHYR_SERVICE_CONTANER_IDL_GENERATOR_HEADER_FILE_H__
#define __ZEPHYR_SERVICE_CONTANER_IDL_GENERATOR_HEADER_FILE_H__
#include "../../Public/include/TypeDef.h"
#include "./baseElement.h"
#include "../../Public/tpl/include/tplmap.h"

namespace Zephyr
{


class CHeaderFile : public CBaseElement
{
public:
    //static CPool<CBaseElement>                            *sm_pKeyWordsPool;


    
protected:
    CBaseElement **m_ppElements;
    char         **m_ppWords;
    EnType         *m_pWordsTypes;
    char          *m_pszFileInPiece;
    TUInt32       m_nNrOfWords;
    TUInt32       m_nNrOfElements;
    TUInt32       m_nFileLength;
    char    *m_pszFile;
    std::string   m_szFileName;
public:
    CHeaderFile();
    ~CHeaderFile();
    TInt32 GeneratorIdl(const char *pFileName);
    
private:
    //读取文件 
    TInt32 ReadFile(const char *pFileName);

    //分词
    TInt32 DividIntoWords();

    

    //第一次语法分析,确定每个词的类型
    TInt32 SyntaxCompile1st();
    //类型组合
    TInt32 SyntaxCompile2nd();
    //生成Idl代码
    TInt32 GeneratorIdlCode();

    TBool  IsDivider(char c);
    TBool  IsEnter(char c);
    TBool  IsOperator(char c);
    TBool  IsAlphabet(char c);
    TBool  IsNum(char c);
    TBool  IsSlashMark(char c)
    {
        if ('/'==c)
        {
            return TRUE;
        }
        return FALSE;
    }
    TBool IsBackSlash(char c)
    {
        if ('\\'==c)
        {
            return TRUE;
        }
        return FALSE;
    }
    TBool  IsStarMark(char c)
    {
        if ('*'==c)
        {
            return TRUE;
        }
        return FALSE;
    }
    TBool IsSingleQuote(char c)
    {
        if ('\''==c)
        {
            return TRUE;
        }
        return FALSE;
    }
    TBool IsQuote(char c)
    {
        if ('"'==c)
        {
            return TRUE;
        }
        return FALSE;
    }
    virtual TInt32 Process(char **ppElements,EnType *pTypes,int nProcess2,int nTotalEles);
    virtual const char *GetHierachyName()
    {   //什么都不需要
        return "";
    }
    void RemoveAllNumLine(); //删除所有'#'
    void RemoveAllCommentsAndMakeConstStr();
    void RemoveAllType(EnType enType);
    void MakeOneWords(char **ppWords,int nFrom,int nWordsNr);
};

}

#endif
