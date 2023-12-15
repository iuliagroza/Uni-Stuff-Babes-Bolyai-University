using System;
using System.Collections.Generic;
using System.Text;

namespace Common
{
    public class HttpParser
    {
        /// <summary>
        /// Parses the HTTP response headers and returns a dictionary of headers.
        /// </summary>
        /// <param name="response">The raw HTTP response string.</param>
        /// <returns>A dictionary with header names as keys and their values as values.</returns>
        public static Dictionary<string, string> ParseResponseHeaders(string response)
        {
            var headers = new Dictionary<string, string>();
            var lines = response.Split(new[] { "\r\n" }, StringSplitOptions.RemoveEmptyEntries);

            // Process the status line
            var statusLine = lines.Length > 0 ? lines[0] : string.Empty;
            headers["Status-Line"] = statusLine;

            // Process headers
            foreach (var line in lines)
            {
                var parts = line.Split(new[] { ": " }, 2, StringSplitOptions.None);
                if (parts.Length == 2)
                {
                    headers[parts[0]] = parts[1];
                }
            }

            return headers;
        }

        /// <summary>
        /// Extracts the Content-Length from the HTTP headers.
        /// </summary>
        /// <param name="headers">The dictionary of HTTP headers.</param>
        /// <returns>The content length as an integer.</returns>
        public static int GetContentLength(Dictionary<string, string> headers)
        {
            if (headers.TryGetValue("Content-Length", out string value) && int.TryParse(value, out int contentLength))
            {
                return contentLength;
            }

            return -1; // -1 indicates that the Content-Length header is not present or invalid.
        }

        /// <summary>
        /// Checks if the response is chunked.
        /// </summary>
        /// <param name="headers">The dictionary of HTTP headers.</param>
        /// <returns>True if the Transfer-Encoding is chunked; otherwise, false.</returns>
        public static bool IsChunkedTransfer(Dictionary<string, string> headers)
        {
            if (headers.TryGetValue("Transfer-Encoding", out string value))
            {
                return value.Equals("chunked", StringComparison.OrdinalIgnoreCase);
            }

            return false;
        }
    }
}
