#ifndef blog_sendpsg
#define blog_sendpsg

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdlib.h>
#include <lwan/lwan.h>
#include <lwan/lwan-mod-serve-files.h>
LWAN_HANDLER(sendpsg)
{
    response->mime_type = "text/html;charset=utf-8";
    
    const char * user       = lwan_request_get_post_param(request,"user");
    const char * token      = lwan_request_get_post_param(request,"token");
    const char * title      = lwan_request_get_post_param(request,"title");
    const char * content    = lwan_request_get_post_param(request,"content");
    if(user==NULL || token==NULL || title==NULL || content==NULL){
        static const char noarg[] = "noarg";
        lwan_strbuf_set_static(response->buffer, noarg, sizeof(noarg) - 1);
        return HTTP_OK;
    }
    
    if(model_user_isLoged(user,token)==0){
        static const char nologin[] = "nologin";
        lwan_strbuf_set_static(response->buffer, nologin, sizeof(nologin) - 1);
        return HTTP_OK;
    }
    
    char idbuf[128];
    model_passage_add(idbuf,128,title,content,user);
    lwan_strbuf_set(response->buffer,idbuf,strlen(idbuf));

    return HTTP_OK;
}

#if defined(__cplusplus)
}
#endif

#endif