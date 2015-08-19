
fredcpp: FRED API Client for C++ {#main}
================================

Overview
--------

`fredcpp` is a third-party C++ library to access [Federal Reserve Economic Data
(FRED&reg;)][fred] database via the web-API as published and maintained by
[Federal Reserve Bank of St. Louis][stlouisfed].

[FRED&reg;][fred] represents an extensive collection of economic data series,
compiled and regularly updated from a large number of data sources. It is one of
the world's most comprehensive online economic databases. Please visit the
official [St. Louis Fed FRED&reg;][fred] site for more information about
FRED&reg; and details on how to obtain FRED API access. There you can also find
excellent [FRED API documentation][fredapi] which references the supported
queries and parameters.

> __DISCLAIMER__: `fredcpp` (FRED API Client for C++) is not affiliated in any
> way with St. Louis Fed and as such is not officially maintained or otherwise
> supported by St. Louis Fed.

`fredcpp` is a free software; the use, copy, and distribution rights are granted
under the terms of the @ref fredcpplicense | [MIT License][fredcpplicense].

[stlouisfed]: http://www.stlouisfed.org "Federal Reserve Bank of St. Louis"
[fred]: http://www.research.stlouisfed.org/fred2/ "Federal Reserve Economic Data (FRED)"
[fredapi]: http://api.stlouisfed.org/docs/fred/ "FRED API documentation"

[fredcpp]: https://github.com/nomadbyte/fredcpp "fredcpp project space"
[fredcppusage]: doc/usage.md "fredcpp Usage"
[fredcpplicense]: LICENSE.md "MIT License"
[fredcppchangelog]: CHANGELOG.md "fredcpp ChangeLog"

[curlcabundle]: http://curl.haxx.se/docs/caextract.html "cURL CA Certificate bundle"


Features
--------

The main objective behind `fredcpp` is to shield C++ users from the details of
constructing and executing web-requests to FRED API, then parsing the results;
at the same time to provide an expressive way to specify FRED data-queries in
C++ context.

`fredcpp` main features:

- access to full set of available FRED entities (_series_, _release_,
  _category_, _source_) and related sub-queries
- uniform and expressive public C++ interface
- built-in HTTP request execution, XML response parsing, and central logging
  facilities
- limited external dependencies (effectively only for HTTP handling)
- __stand-alone ready__ with the supplied implementation for binding with
  cURL-library
- flexible integration with external HTTP stack, XML parser, and logging framework
  alternatives

Additionally, the following concerns are kept in focus:

- portability (relies mainly on STL support)
- ease of build configuration (CMake-based)
- ease of use (example programs supplied)
- extensibility (includes suites of unit and acceptance tests with Google's gtest)
- customization (source-code available to changes per virtues of free software)

Refer to @ref fredcppusage | [fredcpp Usage][fredcppusage] page for more details.

Updates and details about the current version listed in 
@ref fredcppchangelog | [fredcpp ChangeLog][fredcppchangelog].


At-a-glance
-----------

A shortcut to get started with `fredcpp`, assuming you are familiar with
`CMake`, have a C++ compiler, cURL (`libcurl`) library and headers installed.

> __HTTPS-NOTE__: Starting 08/18/2015, FRED API requires HTTPS access for added
> security. `fredcpp` has been updated to generate HTTPS requests. However, `fredcpp`
> users need to make sure that HTTP executor used with `fredcpp` has been
> properly configured to handle HTTPS requests. CA Certificate used by FRED API
> must be available for verification in the user's environment.
>
> To configure `CurlHttpClient` supplied with `fredcpp`, download the CA Certificate
> bundle `cacert.pem` from [cURL CA Extract page][curlcabundle] to the
> `fredcpp` root -- this is needed to run acceptance tests.
> For use once installed, set the evironment variable `CURL_CA_BUNDLE` to point to 
> the downloaded file. Alternatively, call `CurlHttpClient::withCACertFile(path)`
> method to configure this explicitly from the user code, by default the file is
> expected in the running process' work directory.

> __NOTE__: On Windows generate `CMake` files with `"NMake Makefiles"` for MSVC
> `NMAKE`.

From `fredcpp` source directory:

    echo "$FRED_API_KEY" > api.key

    mkdir build
    cd build
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
    make clean all
    make test
    ctest -V

    cd examples
    ./example1
    cat example.txt

Successful?

    make install

Use `fredcpp` library in your projects:

    #include <fredcpp/fredcpp.h>

    #include <fredcpp/external/CurlHttpClient.h>
    #include <fredcpp/external/PugiXmlParser.h>
    #include <fredcpp/external/SimpleLogger.h>

    ......

      fredcpp::Api api;

      api.withLogger( fredcpp::external::SimpleLogger::getInstance() )
         .withExecutor( fredcpp::external::CurlHttpClient::getInstance() )
         .withParser( fredcpp::external::PugiXmlParser::getInstance() )
         ;


      // set your FRED API key

      std::string yourApiKey;

    .......

      api.withKey( yourApiKey );


      // request the recent 10 observations for series "CBIC1"

      fredcpp::Api response;

      api.get( ApiRequestBuilder::SeriesObservations("CBIC1")
                                  .withSort("desc")
                                  .withLimit("10")
              , response );

      if ( !response.good() ) {
        FREDCPP_LOG_ERROR( response.error );
        exit( response.error.status );

      } else {
        FRECPP_LOG_INFO( response );
      }

    ......

Compile and link against the installed `fredcpp` library (assuming installation
with default `/usr/local` prefix):

    g++ example.cpp -lfredcpp -lcurl

More docs:

    make doc

See more examples in `examples` source sub-directory. See the official [FRED API
documentation][fredapi] for details on available requests and parameters.


Building and installation
-------------------------

[CMake](http://www.cmake.org "CMake") is needed to build and install `fredcpp`
library. CMake supports a variety of platforms and C++ compilers and
automatically selects comprehensive compiling options; however, it also allows
manual configuration if needed. Please download and install an up-to-date CMake
release for your platform if required.

1. Unpack the `fredcpp` source-code into a directory and create a
   build directory inside it (for CMake out-of-source build):

       mkdir build

2. Change to the build directory and configure CMake build-parameters (use CMake
   GUI tools, e.g. `cmake-gui` OR specify these on CMake command-line):
   - __Generator type__ - by default CMake chooses platform-specific generators;
     for consistency we prefer makefiles:

         -G "Unix Makefiles"
          OR
         -G "NMake Makefiles"

   - __FRED API key file location__ (`FREDCPP_API_KEY_FILE`) - needed here for
     acceptance testing. By default key is expected in `api.key` file in the
    `fredcpp` source directory
   - __Build type__ (`CMAKE_BUILD_TYPE`) - `Debug` by CMake default, but for
     optimized performance should be set to `RelWithDebInfo` or `Release`
   - __Installation prefix__ (`CMAKE_INSTALL_PREFIX`) - path to directory under
     which to install the resulting `fredcpp` library and headers. CMake provides
     platform-specific defaults.

3. Generate build files - once the parameters are set from CMake GUI, do `Configure`
   then `Generate` to produce the make files/projects:

   Example Windows command line to both configure and generate makefiles (for
   `NMAKE`) at once:

       cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo ..

4. Build all `fredcpp` artifacts - static library, test-runners, and example
   programs will be built in respective sub-directories under the build directory.

   With `"NMake Makefiles"` on Windows, `NMAKE` should be used for `make` command:

       make clean all

5. Run unit and acceptance tests - expect all tests passed:
   > __NOTE__: a valid FRED API key is needed for acceptance tests.

     make test

   To see a more detailed test report, especially when any of the tests has
   failed:

       ctest -V

6. Optionally, examine and run the supplied examples - source code and
   executable files are in `examples` sub-directory of source or `build` directory
   respectively.

7. Optionally, generate documentation files (needs
   [Doxygen](http://www.doxygen.org "Doxygen") installed) - the resulting files are
   in `doc` sub-directory under `build`:

       make doc

8. Install `fredcpp` library and headers:
   > __NOTE__: By default `CMake` uses platform-specific install locations
   > (e.g. `/usr/local` on Linux, `%ProgramFiles%` on Windows etc.).
   > Define `CMAKE_INSTALL_PREFIX` `CMake` variable to override the
   > default install location. E.g. to install under a directory defined by 
   > `$FREDCPP_HOME` environment variable:

     cmake -DCMAKE_INSTALL_PREFIX="$FREDCPP_HOME" ..
     make install

9. Compile and link your program with `fredcpp` referring to the installed include
   and library locations.


Support
-------

We have already been using `fredcpp` in several production applications and
consider it stable for _our_ needs; a couple of new features are planned
(additional HTTP stack bindings). However, with the public release made widely
available, it could generate more feedback - perhaps, feature requests or
improvements, and not too many bug-reports, _hopefully_.

A public issue tracker may be eventually set up to address possible user-feedback.
Meanwhile, please direct your feedback to [fredcpp GitHub project page][fredcpp].

Of course, _Fork us on GitHub!_ as it goes to welcome your contribution.

