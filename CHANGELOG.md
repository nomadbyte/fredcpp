fredcpp ChangeLog  {#fredcppchangelog}
=================

## 0.8.0


## 0.7.0 - 2015-08-19

- Add support for HTTPS access, now required with FRED API
- Update tests and documentation

- __ISSUE__:400:Bad Response returned from FRED API; with debug logging enabled:
  "CURL:Request failed CURLStatus:77|error setting certificate verify locations".
  - FRED API now requires HTTPS access. FRED API CA Certificates must be available
    for verification in user's environment. When using `CurlHttpClient` as executor,
    the CA certificate bundle `cacert.pem` can be downloaded from cURL page
    http://curl.haxx.se/docs/caextract.html. Set an evironment variable
    `CURL_CA_BUNDLE` to point to the downloaded file.

- __ISSUE__:400:Bad Response returned from FRED API; with debug logging enabled:
  "CURL ERROR : error:0D0890A1:asn1 encoding routines:ASN1_verify:unknown message
  digest algorithm".
  - FRED API now requires HTTPS access. When using OpenSSL to handle CA certificate
    verification, version `openssl-0.9.8o` or higher is required.


## 0.6.0 - 2014-03-13

- Add uninstall build target
- Install pugixml headers within fredcpp include
- Cleanup source tree
- Update documentation
- Make request parameters case-insensitive

- __ISSUE__:FRED API parameter "file_type" supports only default "xml" value;
  - All FRED data is properly fetched directly via XML, so other file types are
    just different in formatting conventions. However, an ability to download
    FRED files may be considered as an additional feature if requested.

- __ISSUE__:FRED API parameter "tags" (for categories) is not directly supported.
  - WORKAROUND:Specify in request as a generic parameter via `with("tags","keywords...")`
    method.


## 0.5.0 - 2013-06-25

- __ISSUE__:Unexpected internal-error-500 returned from FRED API for SeriesVintageDates,
  when realtime-end is after last available vintage data for id.
  - WORKAROUND:Just don't make such requests;
    Test added - AT:ErrorWhenRealtimeEndAfterLastSeriesVintageDates

- __ISSUE-FIX__:Bad-request returned from FRED API, while the request was valid.
  - Added retry logic for a failed http request.


## 0.4.0 - 2013-06-02

- Use doxygen to prettify documentation
- Add acceptance tests
- Add fredcpp usage examples
- Restructure includes, move up third-party components
- Add SimpleLogger for a basic logger framework
- Add ApiLog logging facility


## 0.3.0 - 2013-04-02

- Add error processing
- Add expressive requests for FRED series, release, category, and source requests
- Add handling for generic entity request parameters
- Restructure the expressive request interface


## 0.2.0 - 2013-02-23

- Add expressive FRED series-observations request
- Add more unit-tests
- Use gtest for testing
- Restructure ApiResponse
- Use pugixml-1.2 for XML response parsing


## 0.1.0 - 2012-12-16

- Handle a generic FRED request with a raw XML response
- Use `cURL` as http client
- Use stream for http content
- Use a generic http request
