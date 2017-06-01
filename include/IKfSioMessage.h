#ifndef _IKFSIOMESSAGE_H
#define _IKFSIOMESSAGE_H

/*
MIT License
Copyright (c) 2017 Recisio

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

class IKfSioMessage;

typedef IKfSioMessage* KfSioMessagePtr;

typedef struct KfSioMessageListItem {
    KfSioMessagePtr item = nullptr;
    KfSioMessageListItem* next = nullptr;
} KfSioMessageListItem;

typedef KfSioMessageListItem* KfSioMessageList;

class IKfSioMessage {

public:
    /// Creates an INTEGER-typed message
    virtual void KF_CALLCONV create(const int& msg) = 0;
    /// Creates a DOUBLE-typed message
    virtual void KF_CALLCONV create(const double& msg) = 0;
    /// Creates a STRING-typed message
    virtual void KF_CALLCONV create(const char* msg) = 0;
    /// Creates an ARRAY-typed message
    virtual void KF_CALLCONV create(KfSioMessageList msg) = 0;
    /// Creates a BOOLEAN-typed message
    virtual void KF_CALLCONV create(const bool& msg) = 0;

    virtual int KF_CALLCONV getMessageType() const = 0;
    virtual bool KF_CALLCONV isInt() const = 0;
    virtual bool KF_CALLCONV isDouble() const = 0;
    virtual bool KF_CALLCONV isString() const = 0;
    virtual bool KF_CALLCONV isArray() const = 0;
    virtual bool KF_CALLCONV isBool() const = 0;
    virtual bool KF_CALLCONV isNull() const = 0;

    virtual int KF_CALLCONV getInt() const = 0;
    virtual double KF_CALLCONV getDouble() const = 0;
    virtual const char* KF_CALLCONV getString() const = 0;
    virtual KfSioMessageList KF_CALLCONV getArray() const = 0;
    virtual bool KF_CALLCONV getBool() const = 0;

    virtual void KF_CALLCONV releaseArray(KfSioMessageList) const = 0;

};

#endif // _IKFSIOMESSAGE_H
