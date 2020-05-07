/*
  eXosip - This is the eXtended osip library.
  Copyright (C) 2001-2012 Aymeric MOIZARD amoizard@antisip.com
  
  eXosip is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  eXosip is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#ifdef ENABLE_MPATROL
#include <mpatrol.h>
#endif

#ifndef __EXOSIP_H__
#define __EXOSIP_H__

#include <eXosip2/eX_setup.h>
#include <eXosip2/eX_register.h>
#include <eXosip2/eX_call.h>
#include <eXosip2/eX_options.h>
#include <eXosip2/eX_subscribe.h>
#include <eXosip2/eX_refer.h>
#include <eXosip2/eX_message.h>
#include <eXosip2/eX_publish.h>

#include <osipparser2/osip_parser.h>
#include <osipparser2/sdp_message.h>
#include <time.h>

/**
 * @file eXosip.h
 * @brief eXosip API
 *
 * eXosip is a high layer library for rfc3261: the SIP protocol.
 * It offers a simple API to make it easy to use. eXosip2 offers
 * great flexibility for implementing SIP endpoint like:
 * <ul>
 * <li>SIP User-Agents</li>
 * <li>SIP Voicemail or IVR</li>
 * <li>SIP B2BUA</li>
 * <li>any SIP server acting as an endpoint (music server...)</li>
 * </ul>
 *
 * If you need to implement proxy or complex SIP applications,
 * you should consider using osip instead.
 *
 * Here are the eXosip capabilities:
 * <pre>
 *    REGISTER                 to handle registration.
 *    INVITE/BYE               to start/stop VoIP sessions.
 *    INFO                     to send DTMF within a VoIP sessions.
 *    OPTIONS                  to simulate VoIP sessions.
 *    re-INVITE                to modify VoIP sessions
 *    REFER/NOTIFY             to transfer calls.
 *    MESSAGE                  to send Instant Message.
 *    SUBSCRIBE/NOTIFY         to handle presence capabilities.
 *    any other request        to handle what you want!
 * </pre>
 * <P>
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Structure for event description.
 * @var eXosip_event_t
 */
  typedef struct eXosip_event eXosip_event_t;

/**
 * @defgroup eXosip2_authentication eXosip2 authentication API
 * @ingroup eXosip2_msg
 * @{
 */

/**
 * Add authentication credentials. These are used when an outgoing
 * request comes back with an authorization required response.
 *
 * @param excontext    eXosip_t instance.
 * @param username	username
 * @param userid	login (usually equals the username)
 * @param passwd	password
 * @param ha1		currently ignored
 * @param realm		realm within which credentials apply, or NULL
 *			to apply credentials to unrecognized realms
 */
  int eXosip_add_authentication_info (struct eXosip_t *excontext, const char *username, const char *userid, const char *passwd, const char *ha1, const char *realm);

/**
 * Remove authentication credentials.
 *
 * @param excontext    eXosip_t instance.
 * @param username	username
 * @param realm		realm must be exact same arg as for eXosip_add_authentication_info
 */
  int eXosip_remove_authentication_info (struct eXosip_t *excontext, const char *username, const char *realm);

/**
 * Clear all authentication credentials stored in eXosip
 *
 * @param excontext    eXosip_t instance.
 */
  int eXosip_clear_authentication_info (struct eXosip_t *excontext);

/**
 * Initiate some default actions:
 *
 *  Retry with credentials upon reception of 401/407.
 *  Retry with Contact header upon reception of 3xx request.
 *
 *  Usefull & required when eXosip_automatic_action() can't do the automatic action:
 *  1/ if you receive a 401 or 407 for BYE (event EXOSIP_CALL_MESSAGE_REQUESTFAILURE).
 *  2/ if you receive 401 or 407 for any sip request outside of dialog (EXOSIP_MESSAGE_REQUESTFAILURE)
 * 
 * @param excontext    eXosip_t instance.
 * @param je           event to work on.
 */
  int eXosip_default_action (struct eXosip_t *excontext, eXosip_event_t * je);

/**
 * Initiate some automatic actions:
 * 
 *  Refresh REGISTER and SUBSCRIBE before the expiration delay.
 *  Those actions are already done by eXosip_automatic_action();
 *  Prefer eXosip_automatic_action instead of this method.
 *
 * @param excontext    eXosip_t instance.
 */
  void eXosip_automatic_refresh (struct eXosip_t *excontext);

/**
 * Initiate some automatic actions:
 *
 *  Retry with credentials upon reception of 401/407.
 *  Retry with higher Session-Expires upon reception of 422.
 *  Refresh REGISTER and SUBSCRIBE before the expiration delay.
 *  Retry with Contact header upon reception of 3xx request.
 *  Send automatic UPDATE for session-timer feature.
 * 
 * @param excontext    eXosip_t instance.
 */
  void eXosip_automatic_action (struct eXosip_t *excontext);

#ifndef MINISIZE
  /**
 * Automatic internal handling of dialog package.
 * 
 * @param excontext    eXosip_t instance.
 * @param evt          Incoming SUBSCRIBE for dialog package.
 */
  int eXosip_insubscription_automatic (struct eXosip_t *excontext, eXosip_event_t * evt);
#endif

/**
 * Generate random string:
 *
 * @param buf	        destination buffer for random string.
 * @param buf_size      size of destination buffer
 */
  int eXosip_generate_random (char *buf, int buf_size);

/** @} */


/**
 * @defgroup eXosip2_sdp eXosip2 SDP helper API.
 * @ingroup eXosip2_msg
 * @{
 */

/**
 * Get remote SDP body for the latest INVITE of call.
 * 
 * @param excontext    eXosip_t instance.
 * @param did          dialog id of call.
 */
  sdp_message_t *eXosip_get_remote_sdp (struct eXosip_t *excontext, int did);

/**
 * Get local SDP body for the latest INVITE of call.
 * 
 * @param excontext    eXosip_t instance.
 * @param did          dialog id of call.
 */
  sdp_message_t *eXosip_get_local_sdp (struct eXosip_t *excontext, int did);

/**
 * Get local SDP body for the previous latest INVITE of call.
 * 
 * @param excontext    eXosip_t instance.
 * @param did          dialog id of call.
 */
  sdp_message_t *eXosip_get_previous_local_sdp (struct eXosip_t *excontext, int did);

/**
 * Get remote SDP body for the latest INVITE of call.
 * 
 * @param excontext    eXosip_t instance.
 * @param tid          transction id of transaction.
 */
  sdp_message_t *eXosip_get_remote_sdp_from_tid (struct eXosip_t *excontext, int tid);

/**
 * Get local SDP body for the latest INVITE of call.
 * 
 * @param excontext    eXosip_t instance.
 * @param tid          transction id of transaction.
 */
  sdp_message_t *eXosip_get_local_sdp_from_tid (struct eXosip_t *excontext, int tid);

/**
 * Get local SDP body for the given message.
 * 
 * @param message      message containing the SDP.
 */
  sdp_message_t *eXosip_get_sdp_info (osip_message_t * message);

/**
 * Get audio connection information for call.
 * 
 * @param sdp     sdp information.
 */
  sdp_connection_t *eXosip_get_audio_connection (sdp_message_t * sdp);

/**
 * Get audio media information for call.
 * 
 * @param sdp     sdp information.
 */
  sdp_media_t *eXosip_get_audio_media (sdp_message_t * sdp);

/**
 * Get video connection information for call.
 * 
 * @param sdp     sdp information.
 */
  sdp_connection_t *eXosip_get_video_connection (sdp_message_t * sdp);

/**
 * Get video media information for call.
 * 
 * @param sdp     sdp information.
 */
  sdp_media_t *eXosip_get_video_media (sdp_message_t * sdp);

/**
 * Get media connection information for call.
 * 
 * @param sdp     sdp information.
 * @param media   media to search.
 */
  sdp_connection_t *eXosip_get_connection (sdp_message_t * sdp, const char *media);

/**
 * Get media information for call.
 * 
 * @param sdp     sdp information.
 * @param media   media to search.
 */
  sdp_media_t *eXosip_get_media (sdp_message_t * sdp, const char *media);

/** @} */

/**
 * @defgroup eXosip2_event eXosip2 event API
 * @ingroup eXosip2_setup
 * @{
 */

/**
 * Structure for event type description
 * @var eXosip_event_type
 */
  typedef enum eXosip_event_type {
    /* REGISTER related events */
    EXOSIP_REGISTRATION_SUCCESS,       /**0< user is successfully registred.  */
    EXOSIP_REGISTRATION_FAILURE,       /**1< user is not registred.           */

    /* INVITE related events within calls */
    EXOSIP_CALL_INVITE,            /**2< announce a new call                   */
    EXOSIP_CALL_REINVITE,          /**3< announce a new INVITE within call     */

    EXOSIP_CALL_NOANSWER,          /**4< announce no answer within the timeout */
    EXOSIP_CALL_PROCEEDING,        /**5< announce processing by a remote app   */
    EXOSIP_CALL_RINGING,           /**6< announce ringback                     */
    EXOSIP_CALL_ANSWERED,          /**7< announce start of call                */
    EXOSIP_CALL_REDIRECTED,        /**8< announce a redirection                */
    EXOSIP_CALL_REQUESTFAILURE,    /**9< announce a request failure            */
    EXOSIP_CALL_SERVERFAILURE,     /**10< announce a server failure             */
    EXOSIP_CALL_GLOBALFAILURE,     /**11< announce a global failure             */
    EXOSIP_CALL_ACK,               /**12< ACK received for 200ok to INVITE      */

    EXOSIP_CALL_CANCELLED,         /**13< announce that call has been cancelled */

    /* request related events within calls (except INVITE) */
    EXOSIP_CALL_MESSAGE_NEW,              /**14< announce new incoming request. */
    EXOSIP_CALL_MESSAGE_PROCEEDING,       /**15< announce a 1xx for request. */
    EXOSIP_CALL_MESSAGE_ANSWERED,         /**16< announce a 200ok  */
    EXOSIP_CALL_MESSAGE_REDIRECTED,       /**17< announce a failure. */
    EXOSIP_CALL_MESSAGE_REQUESTFAILURE,   /**18< announce a failure. */
    EXOSIP_CALL_MESSAGE_SERVERFAILURE,    /**19< announce a failure. */
    EXOSIP_CALL_MESSAGE_GLOBALFAILURE,    /**20< announce a failure. */

    EXOSIP_CALL_CLOSED,            /**21< a BYE was received for this call      */

    /* for both UAS & UAC events */
    EXOSIP_CALL_RELEASED,             /**22< call context is cleared.            */

    /* response received for request outside calls */
    EXOSIP_MESSAGE_NEW,              /**< announce new incoming request. */
    EXOSIP_MESSAGE_PROCEEDING,       /**< announce a 1xx for request. */
    EXOSIP_MESSAGE_ANSWERED,         /**< announce a 200ok  */
    EXOSIP_MESSAGE_REDIRECTED,       /**< announce a failure. */
    EXOSIP_MESSAGE_REQUESTFAILURE,   /**< announce a failure. */
    EXOSIP_MESSAGE_SERVERFAILURE,    /**< announce a failure. */
    EXOSIP_MESSAGE_GLOBALFAILURE,    /**< announce a failure. */

    /* Presence and Instant Messaging */
    EXOSIP_SUBSCRIPTION_NOANSWER,          /**< announce no answer              */
    EXOSIP_SUBSCRIPTION_PROCEEDING,        /**< announce a 1xx                  */
    EXOSIP_SUBSCRIPTION_ANSWERED,          /**< announce a 200ok                */
    EXOSIP_SUBSCRIPTION_REDIRECTED,        /**< announce a redirection          */
    EXOSIP_SUBSCRIPTION_REQUESTFAILURE,    /**< announce a request failure      */
    EXOSIP_SUBSCRIPTION_SERVERFAILURE,     /**< announce a server failure       */
    EXOSIP_SUBSCRIPTION_GLOBALFAILURE,     /**< announce a global failure       */
    EXOSIP_SUBSCRIPTION_NOTIFY,            /**< announce new NOTIFY request     */

    EXOSIP_IN_SUBSCRIPTION_NEW,            /**< announce new incoming SUBSCRIBE.*/

    EXOSIP_NOTIFICATION_NOANSWER,          /**< announce no answer              */
    EXOSIP_NOTIFICATION_PROCEEDING,        /**< announce a 1xx                  */
    EXOSIP_NOTIFICATION_ANSWERED,          /**< announce a 200ok                */
    EXOSIP_NOTIFICATION_REDIRECTED,        /**< announce a redirection          */
    EXOSIP_NOTIFICATION_REQUESTFAILURE,    /**< announce a request failure      */
    EXOSIP_NOTIFICATION_SERVERFAILURE,     /**< announce a server failure       */
    EXOSIP_NOTIFICATION_GLOBALFAILURE,     /**< announce a global failure       */

    EXOSIP_EVENT_COUNT                  /**< MAX number of events              */
  } eXosip_event_type_t;

/**
 * Structure for event description
 * @struct eXosip_event
 */
  struct eXosip_event {
    eXosip_event_type_t type;               /**< type of the event */
    char textinfo[256];                     /**< text description of event */
    void *external_reference;               /**< external reference (for calls) */

    osip_message_t *request;       /**< request within current transaction */
    osip_message_t *response;      /**< last response within current transaction */
    osip_message_t *ack;           /**< ack within current transaction */

    int tid; /**< unique id for transactions (to be used for answers) */
    int did; /**< unique id for SIP dialogs */

    int rid; /**< unique id for registration */
    int cid; /**< unique id for SIP calls (but multiple dialogs!) */
    int sid; /**< unique id for outgoing subscriptions */
    int nid; /**< unique id for incoming subscriptions */

    int ss_status;  /**< current Subscription-State for subscription */
    int ss_reason;  /**< current Reason status for subscription */
  };

/**
 * Free ressource in an eXosip event.
 * 
 * @param je    event to work on.
 */
  void eXosip_event_free (eXosip_event_t * je);

/**
 * Wait for an eXosip event.
 * 
 * @param excontext    eXosip_t instance.
 * @param tv_s      timeout value (seconds).
 * @param tv_ms     timeout value (mseconds).
 */
  eXosip_event_t *eXosip_event_wait (struct eXosip_t *excontext, int tv_s, int tv_ms);


/**
 * Wait for next eXosip event.
 * **DEPRECATED API**
 * This API will block // You should use eXosip_event_wait instead which is
 * more convenient.
 * limitation: This method will not process automatic 200ok retransmission
 * for INVITE transaction.
 *
 * @param excontext    eXosip_t instance.
 */
  eXosip_event_t *eXosip_event_get (struct eXosip_t *excontext);

/**
 * This socket receive some data yhen an event happens internally.
 * NOTE: you must call eXosip_event_wait until there is no more events
 * in the fifo.
 * 
 * @param excontext    eXosip_t instance.
 */
  int eXosip_event_geteventsocket (struct eXosip_t *excontext);

/** @} */

#ifdef __cplusplus
}
#endif
#endif