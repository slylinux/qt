#include <unistd.h>
#include <iostream>
#include <xlslib.h>

using namespace std;
using namespace xlslib_core;

int main(int argc,char* argv[])
{
  	workbook book;
	worksheet* sheet = book.sheet("测试页");
	book.format("0.00"); /* this one will be lost to us for ever */
	sheet->number(0, 0, 1000); /* must be show as "1000" */
	sheet->number(0, 1, 3.14);

	book.format("yyyy-mm-dd"); /* this one will be lost to us for ever */
	sheet->number(0, 2, 40065.0, FMT_DATE1, 0); /* must be show as "d/m/y" or whatever the local default date format is */

	format_t *datefmt = book.format("yyyy-mm-dd");
	sheet->number(0, 3, 40066.0, FMT_GENERAL, 0)->format(datefmt); /* must be show in custom date format */
	sheet->label(1, 1, "串口数据");
	int err = book.Dump("mytest.xls");
	sheet->label(1, 2, "电量");
	sheet->label(1, 3, "电量2121");
	err = book.Dump("mytest.xls");
	//sWorksheetLabel(sheet, 1, 0, "this is a string", NULL);

	if (err != NO_ERRORS)
	{
		cerr << "failed: I/O failure: " << err << std::endl;
	}

	return 0;
}
