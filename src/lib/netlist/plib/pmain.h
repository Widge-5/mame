// license:BSD-3-Clause
// copyright-holders:Couriersud

#ifndef PMAIN_H_
#define PMAIN_H_

///
/// \file poptions.h
///

#include "palloc.h"
#include "poptions.h"
#include "pstream.h"
#include "pstring.h"
#include "putil.h"

#include <memory>
#include <vector>

#ifdef _WIN32
#include <cwchar>
#define PMAIN(app_class) \
extern "C" int wmain(int argc, wchar_t *argv[]) { return plib::app::run_main<app_class, wchar_t>(argc, argv); }
#else
#define PMAIN(app_class) \
int main(int argc, char **argv) { return plib::app::run_main<app_class, char>(argc, argv); }
#endif


namespace plib {

	/// \brief Application class.
	///
	class app : public options
	{
	public:
		app();

		PCOPYASSIGNMOVE(app, delete)

		virtual ~app() = default;

		virtual pstring usage() = 0;

		/* short version of usage, defaults to usage */
		virtual pstring usage_short() { return usage(); }

		virtual int execute() = 0;

		plib::putf8_fmt_writer std_out;
		plib::putf8_fmt_writer std_err;

		template <class C, typename T>
		static int run_main(int argc, T **argv)
		{
			C application;
			return application.main_utfX(argc, argv);
		}

	private:
		int main_utfX(const std::vector<putf8string> &argv);
		int main_utfX(int argc, char *argv[]);
		int main_utfX(int argc, wchar_t *argv[]);

	};

} // namespace plib



#endif // PMAIN_H_
