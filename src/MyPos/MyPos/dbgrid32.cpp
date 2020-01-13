//Download by http://www.NewXing.com
// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "dbgrid32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// Column properties

long Column::GetAlignment()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

void Column::SetAlignment(long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}

BOOL Column::GetAllowSizing()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void Column::SetAllowSizing(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}

long Column::GetDividerStyle()
{
	long result;
	GetProperty(0x4, VT_I4, (void*)&result);
	return result;
}

void Column::SetDividerStyle(long propVal)
{
	SetProperty(0x4, VT_I4, propVal);
}

CString Column::GetCaption()
{
	CString result;
	GetProperty(0x5, VT_BSTR, (void*)&result);
	return result;
}

void Column::SetCaption(LPCTSTR propVal)
{
	SetProperty(0x5, VT_BSTR, propVal);
}

BOOL Column::GetDataChanged()
{
	BOOL result;
	GetProperty(0x23, VT_BOOL, (void*)&result);
	return result;
}

CString Column::GetDataField()
{
	CString result;
	GetProperty(0x8, VT_BSTR, (void*)&result);
	return result;
}

void Column::SetDataField(LPCTSTR propVal)
{
	SetProperty(0x8, VT_BSTR, propVal);
}

VARIANT Column::GetDefaultValue()
{
	VARIANT result;
	GetProperty(0x9, VT_VARIANT, (void*)&result);
	return result;
}

void Column::SetDefaultValue(const VARIANT& propVal)
{
	SetProperty(0x9, VT_VARIANT, &propVal);
}

short Column::GetColIndex()
{
	short result;
	GetProperty(0xe, VT_I2, (void*)&result);
	return result;
}

float Column::GetLeft()
{
	float result;
	GetProperty(0xf, VT_R4, (void*)&result);
	return result;
}

BOOL Column::GetLocked()
{
	BOOL result;
	GetProperty(0x10, VT_BOOL, (void*)&result);
	return result;
}

void Column::SetLocked(BOOL propVal)
{
	SetProperty(0x10, VT_BOOL, propVal);
}

CString Column::GetNumberFormat()
{
	CString result;
	GetProperty(0x11, VT_BSTR, (void*)&result);
	return result;
}

void Column::SetNumberFormat(LPCTSTR propVal)
{
	SetProperty(0x11, VT_BSTR, propVal);
}

CString Column::GetText()
{
	CString result;
	GetProperty(0x0, VT_BSTR, (void*)&result);
	return result;
}

void Column::SetText(LPCTSTR propVal)
{
	SetProperty(0x0, VT_BSTR, propVal);
}

float Column::GetTop()
{
	float result;
	GetProperty(0x14, VT_R4, (void*)&result);
	return result;
}

VARIANT Column::GetValue()
{
	VARIANT result;
	GetProperty(0x15, VT_VARIANT, (void*)&result);
	return result;
}

void Column::SetValue(const VARIANT& propVal)
{
	SetProperty(0x15, VT_VARIANT, &propVal);
}

BOOL Column::GetVisible()
{
	BOOL result;
	GetProperty(0x16, VT_BOOL, (void*)&result);
	return result;
}

void Column::SetVisible(BOOL propVal)
{
	SetProperty(0x16, VT_BOOL, propVal);
}

float Column::GetWidth()
{
	float result;
	GetProperty(0x17, VT_R4, (void*)&result);
	return result;
}

void Column::SetWidth(float propVal)
{
	SetProperty(0x17, VT_R4, propVal);
}

BOOL Column::GetWrapText()
{
	BOOL result;
	GetProperty(0x25, VT_BOOL, (void*)&result);
	return result;
}

void Column::SetWrapText(BOOL propVal)
{
	SetProperty(0x25, VT_BOOL, propVal);
}

BOOL Column::GetButton()
{
	BOOL result;
	GetProperty(0x28, VT_BOOL, (void*)&result);
	return result;
}

void Column::SetButton(BOOL propVal)
{
	SetProperty(0x28, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// Column operations

CString Column::CellText(const VARIANT& Bookmark)
{
	CString result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		&Bookmark);
	return result;
}

VARIANT Column::CellValue(const VARIANT& Bookmark)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Bookmark);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Columns properties

long Columns::GetCount()
{
	long result;
	GetProperty(0x7d2, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// Columns operations

LPUNKNOWN Columns::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

LPDISPATCH Columns::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

void Columns::SetAdd(short Index)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index);
}

LPDISPATCH Columns::GetAdd(short Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x7d5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		Index);
	return result;
}

void Columns::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7d6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}


/////////////////////////////////////////////////////////////////////////////
// RowBuffer properties

long RowBuffer::GetRowCount()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

void RowBuffer::SetRowCount(long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}

short RowBuffer::GetColumnCount()
{
	short result;
	GetProperty(0x3, VT_I2, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// RowBuffer operations

void RowBuffer::SetBookmark(long Row, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, &newValue);
}

VARIANT RowBuffer::GetBookmark(long Row)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Row);
	return result;
}

CString RowBuffer::GetColumnName(short Col)
{
	CString result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		Col);
	return result;
}

void RowBuffer::SetValue(long Row, short Col, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I2 VTS_VARIANT;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, Col, &newValue);
}

VARIANT RowBuffer::GetValue(long Row, short Col)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I2;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Row, Col);
	return result;
}
