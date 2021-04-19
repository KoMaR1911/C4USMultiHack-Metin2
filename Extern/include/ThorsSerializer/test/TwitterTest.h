#include "Traits.h"
#include <string>
#include <vector>
#include <map>

namespace TwitterTest
{
    using IntVec    = std::vector<int>;
    using Symbol    = std::map<std::string, std::string>;
    using Symbols   = std::vector<Symbol>;

    struct Metadata
    {
        std::string     result_type;
        std::string     iso_language_code;
    };

    struct URL
    {
        std::string     url;
        std::string     expanded_url;
        std::string     display_url;
        IntVec          indices;
    };
    using URLS = std::vector<URL>;

    struct URLObject
    {
        URLS    urls;
    };

    struct Entities
    {
        URLObject*      url         = nullptr;
        URLObject       description;
    };

    struct User
    {
        long            id;
        std::string     id_str;
        std::string     name;
        std::string     screen_name;
        std::string     location;
        std::string     description;
        std::string*    url             = nullptr;
        Entities        entities;
        int             followers_count;
        int             friends_count;
        int             listed_count;
        std::string     created_at;
        int             favourites_count;
        int*            utc_offset      = nullptr;
        std::string*    time_zone       = nullptr;
        bool            geo_enabled;
        bool            verified;
        int             statuses_count;
        std::string     lang;
        bool            contributors_enabled;
        bool            is_translator;
        bool            is_translation_enabled;
        std::string     profile_background_color;
        std::string     profile_background_image_url;
        std::string     profile_background_image_url_https;
        bool            profile_background_tile;
        std::string     profile_image_url;
        std::string     profile_image_url_https;
        std::string*    profile_banner_url  = nullptr;
        std::string     profile_link_color;
        std::string     profile_sidebar_border_color;
        std::string     profile_sidebar_fill_color;
        std::string     profile_text_color;
        bool            profile_use_background_image;
        bool            default_profile;
        bool            default_profile_image;
        bool            following;
        bool            follow_request_sent;
        bool            notifications;
    };
    using Users = std::vector<User>;

    struct Hashtag
    {
        std::string     text;
        IntVec          indices;
    };
    using Hashtags = std::vector<Hashtag>;

    struct UserMention
    {
        std::string     screen_name;
        std::string     name;
        long            id;
        std::string     id_str;
        IntVec          indices;
    };
    using UserMentions = std::vector<UserMention>;

    struct Size
    {
        int             w;
        int             h;
        std::string     resize;
    };

    struct Sizes
    {
        Size            medium;
        Size            small;
        Size            thumb;
        Size            large;
    };

    struct Media
    {
        long            id;
        std::string     id_str;
        IntVec          indices;
        std::string     media_url;
        std::string     media_url_https;
        std::string     url;
        std::string     display_url;
        std::string     expanded_url;
        std::string     type;
        Sizes           sizes;
        long*           source_status_id    = nullptr;
        std::string*    source_status_id_str= nullptr;
    };
    using Medias = std::vector<Media>;

    struct TwitEntities
    {
        Hashtags        hashtags;
        Symbols         symbols;
        URLS            urls;
        UserMentions    user_mentions;
        Medias*         media           = nullptr;
    };

    struct RetweetedStatus
    {
        Metadata        metadata;
        std::string     created_at;
        long            id;
        std::string     id_str;
        std::string     text;
        std::string     source;
        bool            truncated;
        long*           in_reply_to_status_id       = nullptr;
        std::string*    in_reply_to_status_id_str   = nullptr;
        long*           in_reply_to_user_id         = nullptr;
        std::string*    in_reply_to_user_id_str     = nullptr;
        std::string*    in_reply_to_screen_name     = nullptr;
        User            user;
        int*            geo                         = nullptr;
        int*            coordinates                 = nullptr;
        int*            place                       = nullptr;
        int*            contributors                = nullptr;
        int             retweet_count;
        int             favorite_count;
        TwitEntities    entities;
        bool            favorited;
        bool            retweeted;
        bool*           possibly_sensitive          = nullptr;
        std::string     lang;
    };

    struct Status
    {
        Metadata        metadata;
        std::string     created_at;
        long            id;
        std::string     id_str;
        std::string     text;
        std::string     source;
        bool            truncated;
        long*           in_reply_to_status_id       = nullptr;
        std::string*    in_reply_to_status_id_str   = nullptr;
        long*           in_reply_to_user_id         = nullptr;
        std::string*    in_reply_to_user_id_str     = nullptr;
        std::string*    in_reply_to_screen_name     = nullptr;
        User            user;
        int*            geo                         = nullptr;
        int*            coordinates                 = nullptr;
        int*            place                       = nullptr;
        int*            contributors                = nullptr;
        RetweetedStatus*retweeted_status            = nullptr;
        int             retweet_count;
        int             favorite_count;
        TwitEntities    entities;
        bool            favorited;
        bool            retweeted;
        bool*           possibly_sensitive          = nullptr;
        std::string     lang;
    };
    using Statuses = std::vector<Status>;

    struct SearchMetadata
    {
        double          completed_in;
        long            max_id;
        std::string     max_id_str;
        std::string     next_results;
        std::string     query;
        std::string     refresh_url;
        int             count;
        long            since_id;
        std::string     since_id_str;
    };

    struct Twitter
    {
        Statuses        statuses;
        SearchMetadata  search_metadata;
    };
}

ThorsAnvil_MakeTrait(TwitterTest::Metadata, result_type, iso_language_code);
ThorsAnvil_MakeTrait(TwitterTest::URL, url, expanded_url, display_url, indices);
ThorsAnvil_MakeTrait(TwitterTest::URLObject, urls);
ThorsAnvil_MakeTrait(TwitterTest::Entities, url, description);
ThorsAnvil_MakeTrait(TwitterTest::User, id, id_str, name, screen_name, location, description, url, entities, followers_count, friends_count, listed_count, created_at, favourites_count, utc_offset, time_zone, geo_enabled, verified, statuses_count, lang, contributors_enabled, is_translator, is_translation_enabled, profile_background_color, profile_background_image_url, profile_background_image_url_https, profile_background_tile, profile_image_url, profile_image_url_https, profile_banner_url, profile_link_color, profile_sidebar_border_color, profile_sidebar_fill_color, profile_text_color, profile_use_background_image, default_profile, default_profile_image, following, follow_request_sent, notifications);
ThorsAnvil_MakeTrait(TwitterTest::Hashtag, text, indices);
ThorsAnvil_MakeTrait(TwitterTest::UserMention, screen_name, name, id, id_str, indices);
ThorsAnvil_MakeTrait(TwitterTest::Size, w, h, resize);
ThorsAnvil_MakeTrait(TwitterTest::Sizes, medium, small, thumb, large);
ThorsAnvil_MakeTrait(TwitterTest::Media, id, id_str, indices, media_url, media_url_https, url, display_url, expanded_url, type, sizes, source_status_id, source_status_id_str);
ThorsAnvil_MakeTrait(TwitterTest::TwitEntities, hashtags, symbols, urls, user_mentions, media);
ThorsAnvil_MakeTrait(TwitterTest::RetweetedStatus, metadata, created_at, id, id_str, text, source, truncated, in_reply_to_status_id, in_reply_to_status_id_str, in_reply_to_user_id, in_reply_to_user_id_str, in_reply_to_screen_name, user, geo, coordinates, place, contributors, retweet_count, favorite_count, entities, favorited, retweeted, possibly_sensitive, lang);
ThorsAnvil_MakeTrait(TwitterTest::Status, metadata, created_at, id, id_str, text, source, truncated, in_reply_to_status_id, in_reply_to_status_id_str, in_reply_to_user_id, in_reply_to_user_id_str, in_reply_to_screen_name, user, geo, coordinates, place, contributors, retweeted_status, retweet_count, favorite_count, entities, favorited, retweeted, possibly_sensitive, lang);
ThorsAnvil_MakeTrait(TwitterTest::SearchMetadata, completed_in, max_id, max_id_str, next_results, query, refresh_url, count, since_id, since_id_str);
ThorsAnvil_MakeTrait(TwitterTest::Twitter, statuses, search_metadata);

