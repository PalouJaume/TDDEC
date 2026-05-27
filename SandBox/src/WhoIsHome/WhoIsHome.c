#include "WhoIsHome.h"

#include "RFIDService.h"
#include "EmailService.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct WHOISHOME_DATA
{
    int cnt_in;
    int in[10];
    int cnt_out;
    int out[10];
} WHOISHOME_DATA;

static WHOISHOME_DATA process_events(RFID_EVENT *events, int eventc)
{
    WHOISHOME_DATA data = {
        .cnt_in = 0,
        .in = {0},
        .cnt_out = 0,
        .out = {0},
    };

    for (int i = 0; i < eventc; i++)
    {
        switch (events[i].kind)
        {
        case IN_RANGE:
            data.in[data.cnt_in] = events[i].id;
            data.cnt_in++;
            break;

        case OUT_RANGE:
            data.out[data.cnt_out] = events[i].id;
            data.cnt_out++;
            break;

        default:
            break;
        }
    }

    return data;
}

static void buffer_ids(char **buff_in, char **buff_out, WHOISHOME_DATA data)
{
    *buff_in = NULL;
    *buff_out = NULL;

    int max_len_in = (data.cnt_in * 4) + 1;
    char *in = malloc(max_len_in * sizeof(char));
    if (in == NULL)
        goto error;
    for (int i = 0; i < max_len_in; i++)
        in[i] = '\0';

    int index_in = 0;
    for (int i = 0; i < data.cnt_in; i++)
    {
        snprintf(in + index_in, 4, "%d ", data.in[i]);
        index_in = strlen(in);
    }
    in[index_in - 1] = '\0';

    *buff_in = in;

    int max_len_out = (data.cnt_out * 4) + 1;
    char *out = malloc(max_len_out * sizeof(char));
    if (in == NULL)
        goto error_out;
    for (int i = 0; i < max_len_out; i++)
        out[i] = '\0';

    int index_out = 0;
    for (int i = 0; i < data.cnt_out; i++)
    {
        snprintf(out + index_out, 4, "%d ", data.out[i]);
        index_out = strlen(out);
    }
    out[index_out - 1] = '\0'; 

    *buff_out = out;
    return;
error_out:
    free(in);
    *buff_in = NULL;
    return;
error:
    return;
}

void WhoIsHome_Create(void)
{
}

void WhoIsHome_Update(RFID_EVENT *events, int eventc)
{
    if (events == NULL || eventc <= 0)
        return;

    WHOISHOME_DATA data = process_events(events, eventc);

    char subject[256] = {'\0'};
    char body[256] = {'\0'};
    EMAIL_PACK email = {.to = EMAIL_MANAGER,
                        .subject = subject,
                        .body = body};

    snprintf(subject, 256, "%d RFID in range, %d RFID out range",
             data.cnt_in,
             data.cnt_out);

    char *in_ids = NULL;
    char *out_ids = NULL;

    buffer_ids(&in_ids, &out_ids, data);

    snprintf(body, 256, "IN RANGE RFIDs: %s\n OUT RANGE RFIDs: %s",
             (in_ids != NULL && data.cnt_in > 0) ? in_ids : "None",
             (out_ids != NULL && data.cnt_out > 0) ? out_ids : "None");

    EmailService_Send(email);

    if (in_ids != NULL)
        free(in_ids);
    if (out_ids != NULL)
        free(out_ids);
}

void WhoIsHome_Destroy(void)
{
}