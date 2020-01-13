//Download by http://www.NewXing.com
// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// Column wrapper class

class Column : public COleDispatchDriver
{
public:
	Column() {}		// Calls COleDispatchDriver default constructor
	Column(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Column(const Column& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetAlignment();
	void SetAlignment(long);
	BOOL GetAllowSizing();
	void SetAllowSizing(BOOL);
	long GetDividerStyle();
	void SetDividerStyle(long);
	CString GetCaption();
	void SetCaption(LPCTSTR);
	BOOL GetDataChanged();
	CString GetDataField();
	void SetDataField(LPCTSTR);
	VARIANT GetDefaultValue();
	void SetDefaultValue(const VARIANT&);
	short GetColIndex();
	float GetLeft();
	BOOL GetLocked();
	void SetLocked(BOOL);
	CString GetNumberFormat();
	void SetNumberFormat(LPCTSTR);
	CString GetText();
	void SetText(LPCTSTR);
	float GetTop();
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	BOOL GetVisible();
	void SetVisible(BOOL);
	float GetWidth();
	void SetWidth(float);
	BOOL GetWrapText();
	void SetWrapText(BOOL);
	BOOL GetButton();
	void SetButton(BOOL);

// Operations
public:
	CString CellText(const VARIANT& Bookmark);
	VARIANT CellValue(const VARIANT& Bookmark);
};
/////////////////////////////////////////////////////////////////////////////
// Columns wrapper class

class Columns : public COleDispatchDriver
{
public:
	Columns() {}		// Calls COleDispatchDriver default constructor
	Columns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Columns(const Columns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetCount();

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH GetItem(const VARIANT& Index);
	void SetAdd(short Index);
	LPDISPATCH GetAdd(short Index);
	void Remove(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// RowBuffer wrapper class

class RowBuffer : public COleDispatchDriver
{
public:
	RowBuffer() {}		// Calls COleDispatchDriver default constructor
	RowBuffer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	RowBuffer(const RowBuffer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetRowCount();
	void SetRowCount(long);
	short GetColumnCount();

// Operations
public:
	void SetBookmark(long Row, const VARIANT& newValue);
	VARIANT GetBookmark(long Row);
	CString GetColumnName(short Col);
	void SetValue(long Row, short Col, const VARIANT& newValue);
	VARIANT GetValue(long Row, short Col);
};
