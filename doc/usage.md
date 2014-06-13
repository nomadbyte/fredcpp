
Access FRED data using fredcpp {#fredcppusage}
==============================

`fredcpp` is a third-party FRED API Client for C++. It allows access to [Federal
Reserve Economic Data (FRED&reg;)][fred] database via the web-API as published
and maintained by [Federal Reserve Bank of St. Louis][stlouisfed].

[stlouisfed]: http://www.stlouisfed.org "Federal Reserve Bank of St. Louis"
[fred]: http://www.research.stlouisfed.org/fred2/ "Federal Reserve Economic Data (FRED)"
[fredapi]: http://api.stlouisfed.org/docs/fred/ "FRED API documentation"
[fredcpp]: https://github.com/nomadbyte/fredcpp "fredcpp project space"

Supported FRED requests
-----------------------

`fredcpp` aims to support the major set of available FRED API requests and entities.
Please visit the official [St. Louis Fed FRED&reg;][fred] site for more information about
FRED&reg; and details on how to obtain FRED API access. There you can also find
excellent [FRED API documentation][fredapi] which references the supported
queries and parameters.

`fredcpp` defines expressive syntax to facilitate valid FRED API query
construction in C++ context. Each supported query has a request class defined,
which includes only the parameters applicable to the query. In general, name
of a request class corresponds to the FRED API entity query path.

> __NOTE__: fredcpp::ApiRequestBuilder static methods help generate the requests
> that correspond to the FRED API query.

    fredcpp::ApiRequestBuilder::SeriesUpdates();  // "series/updates" request

Listed below are FRED API entity paths and the corresponding `fredcpp` request
classes defined:

__Category__:

- "category"            |  fredcpp::FredCategoryRequest
- "category/related"    |  fredcpp::FredCategoryRelatedRequest
- "category/series"     |  fredcpp::FredCategorySeriesRequest
- "category/children"   |  fredcpp::FredCategoryChildrenRequest

__Release__:

- "release"             |  fredcpp::FredReleaseRequest
- "release/series"      |  fredcpp::FredReleaseSeriesRequest
- "release/sources"     |  fredcpp::FredReleaseSourcesRequest
- "release/dates"       |  fredcpp::FredReleaseDatesRequest
- "releases/dates"      |  fredcpp::FredReleasesDatesRequest
- "releases"            |  fredcpp::FredReleasesRequest

__Series__:

- "series"              |  fredcpp::FredSeriesRequest
- "series/observations" |  fredcpp::FredSeriesObservationsRequest
- "series/releases"     |  fredcpp::FredSeriesReleaseRequest
- "series/categories"   |  fredcpp::FredSeriesCategoriesRequest
- "series/vintagedates" |  fredcpp::FredSeriesVintageDatesRequest
- "series/updates"      |  fredcpp::FredSeriesUpdatesRequest
- "series/search"       |  fredcpp::FredSeriesSearchRequest

__Source__:

- "source"              |  fredcpp::FredSourceRequest
- "source/releases"     |  fredcpp::FredSourceReleasesRequest
- "sources"             |  fredcpp::FredSourcesRequest


Supported FRED API parameters are added to a `fredcpp` request using corresponding
`with`-methods.

> __NOTE__: Additional request parameters can be call-chained.

    fredcpp::ApiRequestBuilder::SeriesUpdates()
                .withLimit("10")
                .withFilter("macro")
                ;

In general the naming is similar, abbreviated in some cases. Refer to individual
`fredcpp` request classes for list of available parameters (e.g.
fredcpp::FredSeriesObservationsRequest ).


Getting FRED data
-----------------

FRED API requests are executed through fredcpp::Api class, which coordinates
creation of an HTTP request, its execution and processing of the response contents.

fredcpp::Api uses binding interfaces to an external HTTP client stack, an XML
parser, and a logging framework. `fredcpp` source includes implementation for the
following bindings:

- cURL (`libcurl`) | fredcpp::external::CurlHttpClient
- `pugixml`        | fredcpp::external::PugiXmlParser
- Simple logger    | fredcpp::external::SimpleLogger

> __NOTE__: Alternative bindings may be similarly implemented per needs of your
> user or system configuration (e.g. bind with `log4cpp` framework etc.).
> To use alternative bindings for either of the facilities, implement corresponding
> interfaces:
>
> - fredcpp::internal::HttpRequestExecutor
> - fredcpp::internal::XmlResponseParser
> - fredcpp::internal::Logger

Configure fredcpp::Api, by specifing the bindings to the external facilities and
also setting your FRED API key. Once configured, the general usage is as follows:

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

On successful request the resulting FRED data is returned in fredcpp::ApiResponse
object, as specified in fredcpp::Api::get argument. Generally, the returned data
is structured into result descriptor, and an array of entities. The data is stored
in fredcpp::ApiEntity type and can be accessed directly via attributes, as defined
in FRED API:

    // E.g.: "category/series" response

    std::string seriesId = response.entities[0].attributes("id");
    std::string orderBy = response.result.attributes("order_by");

> __NOTE__: Mostly the FRED data is returned in attributes. However, several requests
> return entities that also have a value (in addition to attributes).

    // E.g.: "release/dates" returns release date as a value, not an attribute

    std::string date = releaseDates.entities[0].value;
    std::string releaseId = releaseDates.entities[0].attribute("release_id");

Refer to the included example programs for more details. By default, the example
programs are built as part of `fredcpp` build configuration and may be executed
from build examples directory.


Error handling
--------------

In general `fredcpp` use the errors may arise in the following situations:

- __Bad-request, Good-execution__ - user error, incorrect parameter values were
  submitted. `fredcpp` executed the request, yet FRED API rejected it, returning
   "Bad request" result.
- __Good-request, Bad-execution__ - request execution failed (HTTP failure,
   FRED API is unavailabe, unexpected content received, etc.)
- __System or process problem__ - exceptions, resource starvation, segmentation
   fault, etc.

The first two situations result in a bad response, which can be tested with
fredcpp::ApiResponse as:

    if ( !response.good() ) {
      // Bad response
      FREDCPP_LOG_ERROR( response.error );
      exit (response.error.status);
    }

The error message is available from fredcpp::ApiError, as is the status, to
provide error details.

`fredcpp` execution errors are logged internally via fredcpp::ApiLog Logging
Facility prior to being returned back to user-program. However, user errors (such as
Bad-Request) are returned without logging, so it's left to the user-program context
to decide how to treat it.

`fredcpp` Logging Facility is mainly used through @ref FREDCPP_LOG "Logging Helper Macros"
which forward logged message to the external logger framework bound to the
fredcpp::Api instance.

> __NOTE__: Supplied examples demonstrate the `fredcpp` usage with
> fredcpp::external::SimpleLogger logging framework. Alternative bindings may be
> added by implementing fredcpp::internal::Logger interface for the logging
> framework of choice.

The errors caused due to system of process problems are not handled internally in
`fredcpp` and are propagated to the user-context.


Feedback
--------

We appreciate user feedback and hope `fredcpp` will be of utility to bring the
wealth of FRED data to your applications.

Let us know your experience with `fredcpp`, any bugs found, contributions, or
improvement features. Currently, [fredcpp project space][fredcpp] is the preferred
place to consolidate the interaction about it. Alternatively, you may direct
your feedback to [fredcpp\@at\@nomadbyte.com](mailto:fredcpp@at@nomadbyte.com) .

