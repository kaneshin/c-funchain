#include <stdio.h>
#include <stdlib.h>

struct _session {
    char *table;
    char *cols;
    char *cond;
    char buf[256];

    struct _session *(*get)(struct _session *self, char *table);
    struct _session *(*select)(struct _session *self, char *cols);
    struct _session *(*where)(struct _session *self, char *cond);
    char *(*query)(struct _session *self);
};
typedef struct _session session;
typedef session *session_ref;

session_ref
session_get(session_ref self, char *table)
{
    self->table = table;
    return self;
}

session_ref
session_select(session_ref self, char *cols)
{
    self->cols = cols;
    return self;
}

session_ref
session_where(session_ref self, char *cond)
{
    self->cond = cond;
    return self;
}

char *
session_query(session_ref self)
{
    sprintf(self->buf, "SELECT %s FROM %s WHERE %s", self->cols, self->table, self->cond);
    return self->buf;
}

session_ref
new_session()
{
    session_ref sess = (session_ref)malloc(sizeof(session));
    sess->table = NULL;
    sess->cols = NULL;
    sess->cond = NULL;
    sess->get = session_get;
    sess->select = session_select;
    sess->where = session_where;
    sess->query = session_query;
    return sess;
}

int
main(int argc, char* argv[])
{
    session_ref sess = new_session();
    printf("%s\n", sess->select(sess, "id,name")->where(sess, "id = 1")->get(sess, "user")->query(sess));
    return 0;
}
