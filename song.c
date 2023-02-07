typedef struct song {
    char    *artist;
    char    *name;
    int length;

    struct song *next;
    struct song *prev;
} song_t;