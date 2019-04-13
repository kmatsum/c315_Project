#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <curl/curl.h>

typedef struct string_buffer_s
{
    char * ptr;
    size_t len;
} string_buffer_t;


static void string_buffer_initialize( string_buffer_t * sb )
{
    sb->len = 0;
    sb->ptr = malloc(sb->len+1);
    sb->ptr[0] = '\0';
}


static void string_buffer_finish( string_buffer_t * sb )
{
    free(sb->ptr);
    sb->len = 0;
    sb->ptr = NULL;
}


static size_t string_buffer_callback( void * buf, size_t size, size_t nmemb, void * data )
{
    string_buffer_t * sb = data;
    size_t new_len = sb->len + size * nmemb;

    sb->ptr = realloc( sb->ptr, new_len + 1 );

    memcpy( sb->ptr + sb->len, buf, size * nmemb );

    sb->ptr[ new_len ] = '\0';
    sb->len = new_len;

    return size * nmemb;

}


static size_t header_callback(char * buf, size_t size, size_t nmemb, void * data )
{
    return string_buffer_callback( buf, size, nmemb, data );
}


static size_t write_callback( void * buf, size_t size, size_t nmemb, void * data )
{
    return string_buffer_callback( buf, size, nmemb, data );
}


int randomNumberAPICall()
{
    CURL * curl;
    CURLcode res;
    string_buffer_t strbuf;

    char * myurl = "https://www.random.org/integers/?num=1&min=1&max=100&col=1&base=10&format=plain&rnd=new";;

    string_buffer_initialize( &strbuf );

    curl = curl_easy_init();

    if(!curl)
    {
        fprintf(stderr, "Fatal: curl_easy_init() error.\n");
        string_buffer_finish( &strbuf );
        return EXIT_FAILURE;
    }

    curl_easy_setopt(curl, CURLOPT_URL, myurl );
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L );
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback );
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback );
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strbuf );
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &strbuf );

    res = curl_easy_perform(curl);

    if( res != CURLE_OK )
    {
        fprintf( stderr, "Request failed: curl_easy_perform(): %s\n", curl_easy_strerror(res) );

        curl_easy_cleanup( curl );
        string_buffer_finish( &strbuf );

        return EXIT_FAILURE;
    }


    printf( "%s\n\n", strbuf.ptr );

    curl_easy_cleanup( curl );
    string_buffer_finish( &strbuf );

    return EXIT_SUCCESS;
}

/* eof */