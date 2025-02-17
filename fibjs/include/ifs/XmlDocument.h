/***************************************************************************
 *                                                                         *
 *   This file was automatically generated using idlc.js                   *
 *   PLEASE DO NOT EDIT!!!!                                                *
 *                                                                         *
 ***************************************************************************/

#pragma once

/**
 @author Leo Hoo <lion@9465.net>
 */

#include "../object.h"
#include "ifs/XmlNode.h"

namespace fibjs {

class XmlNode_base;
class Buffer_base;
class XmlDocumentType_base;
class XmlElement_base;
class XmlNodeList_base;
class XmlText_base;
class XmlComment_base;
class XmlCDATASection_base;
class XmlProcessingInstruction_base;

class XmlDocument_base : public XmlNode_base {
    DECLARE_CLASS(XmlDocument_base);

public:
    // XmlDocument_base
    static result_t _new(exlib::string type, obj_ptr<XmlDocument_base>& retVal, v8::Local<v8::Object> This = v8::Local<v8::Object>());
    virtual result_t load(exlib::string source) = 0;
    virtual result_t load(Buffer_base* source) = 0;
    virtual result_t get_inputEncoding(exlib::string& retVal) = 0;
    virtual result_t get_xmlStandalone(bool& retVal) = 0;
    virtual result_t set_xmlStandalone(bool newVal) = 0;
    virtual result_t get_xmlVersion(exlib::string& retVal) = 0;
    virtual result_t set_xmlVersion(exlib::string newVal) = 0;
    virtual result_t get_doctype(obj_ptr<XmlDocumentType_base>& retVal) = 0;
    virtual result_t get_documentElement(obj_ptr<XmlElement_base>& retVal) = 0;
    virtual result_t get_head(obj_ptr<XmlElement_base>& retVal) = 0;
    virtual result_t get_title(exlib::string& retVal) = 0;
    virtual result_t get_body(obj_ptr<XmlElement_base>& retVal) = 0;
    virtual result_t getElementsByTagName(exlib::string tagName, obj_ptr<XmlNodeList_base>& retVal) = 0;
    virtual result_t getElementsByTagNameNS(exlib::string namespaceURI, exlib::string localName, obj_ptr<XmlNodeList_base>& retVal) = 0;
    virtual result_t getElementById(exlib::string id, obj_ptr<XmlElement_base>& retVal) = 0;
    virtual result_t getElementsByClassName(exlib::string className, obj_ptr<XmlNodeList_base>& retVal) = 0;
    virtual result_t createElement(exlib::string tagName, obj_ptr<XmlElement_base>& retVal) = 0;
    virtual result_t createElementNS(exlib::string namespaceURI, exlib::string qualifiedName, obj_ptr<XmlElement_base>& retVal) = 0;
    virtual result_t createTextNode(exlib::string data, obj_ptr<XmlText_base>& retVal) = 0;
    virtual result_t createComment(exlib::string data, obj_ptr<XmlComment_base>& retVal) = 0;
    virtual result_t createCDATASection(exlib::string data, obj_ptr<XmlCDATASection_base>& retVal) = 0;
    virtual result_t createProcessingInstruction(exlib::string target, exlib::string data, obj_ptr<XmlProcessingInstruction_base>& retVal) = 0;

public:
    template <typename T>
    static void __new(const T& args);

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_load(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_get_inputEncoding(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_xmlStandalone(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_set_xmlStandalone(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args);
    static void s_get_xmlVersion(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_set_xmlVersion(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args);
    static void s_get_doctype(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_documentElement(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_head(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_title(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_body(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_getElementsByTagName(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_getElementsByTagNameNS(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_getElementById(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_getElementsByClassName(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_createElement(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_createElementNS(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_createTextNode(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_createComment(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_createCDATASection(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_createProcessingInstruction(const v8::FunctionCallbackInfo<v8::Value>& args);
};
}

#include "ifs/Buffer.h"
#include "ifs/XmlDocumentType.h"
#include "ifs/XmlElement.h"
#include "ifs/XmlNodeList.h"
#include "ifs/XmlText.h"
#include "ifs/XmlComment.h"
#include "ifs/XmlCDATASection.h"
#include "ifs/XmlProcessingInstruction.h"

namespace fibjs {
inline ClassInfo& XmlDocument_base::class_info()
{
    static ClassData::ClassMethod s_method[] = {
        { "load", s_load, false, false },
        { "getElementsByTagName", s_getElementsByTagName, false, false },
        { "getElementsByTagNameNS", s_getElementsByTagNameNS, false, false },
        { "getElementById", s_getElementById, false, false },
        { "getElementsByClassName", s_getElementsByClassName, false, false },
        { "createElement", s_createElement, false, false },
        { "createElementNS", s_createElementNS, false, false },
        { "createTextNode", s_createTextNode, false, false },
        { "createComment", s_createComment, false, false },
        { "createCDATASection", s_createCDATASection, false, false },
        { "createProcessingInstruction", s_createProcessingInstruction, false, false }
    };

    static ClassData::ClassProperty s_property[] = {
        { "inputEncoding", s_get_inputEncoding, block_set, false },
        { "xmlStandalone", s_get_xmlStandalone, s_set_xmlStandalone, false },
        { "xmlVersion", s_get_xmlVersion, s_set_xmlVersion, false },
        { "doctype", s_get_doctype, block_set, false },
        { "documentElement", s_get_documentElement, block_set, false },
        { "head", s_get_head, block_set, false },
        { "title", s_get_title, block_set, false },
        { "body", s_get_body, block_set, false }
    };

    static ClassData s_cd = {
        "XmlDocument", false, s__new, NULL,
        ARRAYSIZE(s_method), s_method, 0, NULL, ARRAYSIZE(s_property), s_property, 0, NULL, NULL, NULL,
        &XmlNode_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void XmlDocument_base::s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CONSTRUCT_INIT();
    __new(args);
}

template <typename T>
void XmlDocument_base::__new(const T& args)
{
    obj_ptr<XmlDocument_base> vr;

    CONSTRUCT_ENTER();

    METHOD_OVER(1, 0);

    OPT_ARG(exlib::string, 0, "text/xml");

    hr = _new(v0, vr, args.This());

    CONSTRUCT_RETURN();
}

inline void XmlDocument_base::s_load(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    METHOD_INSTANCE(XmlDocument_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = pInst->load(v0);

    METHOD_OVER(1, 1);

    ARG(obj_ptr<Buffer_base>, 0);

    hr = pInst->load(v0);

    METHOD_VOID();
}

inline void XmlDocument_base::s_get_inputEncoding(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_INSTANCE(XmlDocument_base);
    PROPERTY_ENTER();

    hr = pInst->get_inputEncoding(vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_get_xmlStandalone(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    bool vr;

    METHOD_INSTANCE(XmlDocument_base);
    PROPERTY_ENTER();

    hr = pInst->get_xmlStandalone(vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_set_xmlStandalone(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args)
{
    METHOD_INSTANCE(XmlDocument_base);
    PROPERTY_ENTER();
    PROPERTY_VAL(bool);

    hr = pInst->set_xmlStandalone(v0);

    PROPERTY_SET_LEAVE();
}

inline void XmlDocument_base::s_get_xmlVersion(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_INSTANCE(XmlDocument_base);
    PROPERTY_ENTER();

    hr = pInst->get_xmlVersion(vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_set_xmlVersion(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args)
{
    METHOD_INSTANCE(XmlDocument_base);
    PROPERTY_ENTER();
    PROPERTY_VAL(exlib::string);

    hr = pInst->set_xmlVersion(v0);

    PROPERTY_SET_LEAVE();
}

inline void XmlDocument_base::s_get_doctype(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlDocumentType_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    PROPERTY_ENTER();

    hr = pInst->get_doctype(vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_get_documentElement(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlElement_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    PROPERTY_ENTER();

    hr = pInst->get_documentElement(vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_get_head(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlElement_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    PROPERTY_ENTER();

    hr = pInst->get_head(vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_get_title(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_INSTANCE(XmlDocument_base);
    PROPERTY_ENTER();

    hr = pInst->get_title(vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_get_body(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlElement_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    PROPERTY_ENTER();

    hr = pInst->get_body(vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_getElementsByTagName(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlNodeList_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = pInst->getElementsByTagName(v0, vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_getElementsByTagNameNS(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlNodeList_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    METHOD_ENTER();

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(exlib::string, 1);

    hr = pInst->getElementsByTagNameNS(v0, v1, vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_getElementById(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlElement_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = pInst->getElementById(v0, vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_getElementsByClassName(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlNodeList_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = pInst->getElementsByClassName(v0, vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_createElement(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlElement_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = pInst->createElement(v0, vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_createElementNS(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlElement_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    METHOD_ENTER();

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(exlib::string, 1);

    hr = pInst->createElementNS(v0, v1, vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_createTextNode(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlText_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = pInst->createTextNode(v0, vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_createComment(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlComment_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = pInst->createComment(v0, vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_createCDATASection(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlCDATASection_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = pInst->createCDATASection(v0, vr);

    METHOD_RETURN();
}

inline void XmlDocument_base::s_createProcessingInstruction(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<XmlProcessingInstruction_base> vr;

    METHOD_INSTANCE(XmlDocument_base);
    METHOD_ENTER();

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(exlib::string, 1);

    hr = pInst->createProcessingInstruction(v0, v1, vr);

    METHOD_RETURN();
}
}
