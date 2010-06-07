/*
   libmapiserver - MAPI library for Server side

   OpenChange Project

   Copyright (C) Julien Kerihuel 2009

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef	__LIBMAPISERVER_H__
#define	__LIBMAPISERVER_H__

#ifndef	_GNU_SOURCE
#define	_GNU_SOURCE 1
#endif

#include <sys/types.h>

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <dcerpc.h>
#include <param.h>

#include <gen_ndr/exchange.h>

#ifndef	__BEGIN_DECLS
#ifdef	__cplusplus
#define	__BEGIN_DECLS		extern "C" {
#define	__END_DECLS		}
#else
#define	__BEGIN_DECLS
#define	__END_DECLS
#endif
#endif

#define	SIZE_DFLT_MAPI_RESPONSE	6

/* Rops default and static size */

/**
   \details OpenFolderRop has fixed response size for
   -# HasRules: uint8_t
   -# IsGhosted: uint8_t   
 */
#define	SIZE_DFLT_ROPOPENFOLDER			2

/**
   \details OpenMessage has fixed response size for
   -# HasNamedProperties: uint8_t
   -# RecipientCount: uint16_t
   -# RowCount: uint8_t
 */
#define	SIZE_DFLT_ROPOPENMESSAGE		4

/**
   \details GetHierarchyTableTop has fixed response size for:
   -# RowCount: uint32_t
 */
#define	SIZE_DFLT_ROPGETHIERARCHYTABLE		4

/**
   \details GetContentsTableRop has fixed response size for:
   -# RowCount: uint32_t
 */
#define	SIZE_DFLT_ROPGETCONTENTSTABLE		4

/**
   \details CreateMessageRop has fixed response size for:
   -# HasMessageId: uint8_t
 */
#define	SIZE_DFLT_ROPCREATEMESSAGE		1

/**
   \details GetPropertiesSpecificRop has fixed response size for:
   -# layout: uint8_t
 */
#define	SIZE_DFLT_ROPGETPROPERTIESSPECIFIC	1

/**
   \details: SetPropertiesRop has fixed response size for:
   -# PropertyProblemCount: uint16_t
 */
#define	SIZE_DFLT_ROPSETPROPERTIES		2

/**
   \details: DeletePropertiesRop has fixed response size for:
   -# PropertyProblemCount: uint16_t
 */
#define	SIZE_DFLT_ROPDELETEPROPERTIES		2

/**
   \details: SaveChangesMessageRop has fixed response size for:
   -# handle_idx: uint8_t
   -# MessageId: uint64_t
 */
#define	SIZE_DFLT_ROPSAVECHANGESMESSAGE		9

/**
   \details: SetMessageReadFlagRop has fixed response size for:
   -# ReadStatusChanged: uint8_t
 */
#define	SIZE_DFLT_ROPSETMESSAGEREADFLAG		1

/**
   \details SetColumnsRop has fixed response size for:
   -# TableStatus: uint8_t
 */
#define	SIZE_DFLT_ROPSETCOLUMNS			1

/**
   \details SortTableRop has fixed response size for:
   -# TableStatus: uint8_t
 */
#define	SIZE_DFLT_ROPSORTTABLE			1

/**
   \details RestrictRop has fixed response size for:
   -# TableStatus: uint8_t
 */
#define	SIZE_DFLT_ROPRESTRICT			1

/**
   \details QueryRowsRop has fixed size for:
   -# Origin: uint8_t
   -# RowCount: uint16_t
 */
#define	SIZE_DFLT_ROPQUERYROWS			3

/**
   \details QueryPositionRop has fixed response size for:
   -# Numerator: uint32_t
   -# Denominator: uint32_t
 */
#define	SIZE_DFLT_ROPQUERYPOSITION		8

/**
   \details SeekRowRop has fixed response size for:
   -# HasSought: uint8_t
   -# RowsSought: uint32_t
 */
#define	SIZE_DFLT_ROPSEEKROW			5

/**
   \details CreateFolderRop has fixed response size for:
   -# folder_id: uint64_t
   -# isExistingFolder: uint8_t
 */
#define	SIZE_DFLT_ROPCREATEFOLDER		9

/**
   \details DeleteFolderRop has fixed response size for:
   -# PartialCompletion: uint8_t
 */
#define	SIZE_DFLT_ROPDELETEFOLDER		1


/**
   \details OpenStreamRop has fixed response size for:
   -# StreamSize: uint16_t
 */
#define	SIZE_DFLT_ROPOPENSTREAM			2

/**
   \details GetReceiveFolder has fixed response size for:
   -# folder_id: uint64_t
 */
#define	SIZE_DFLT_ROPGETRECEIVEFOLDER		8

/**
   \details GetAddressTypes has fixed response size for:
   -# cValues: uint16_t
   -# size: uint16_t
 */
#define	SIZE_DFLT_ROPGETADDRESSTYPES		4

/**
   \details GetTransportFolder has fixed response size for:
   -# FolderId: uint64_t
 */
#define	SIZE_DFLT_ROPGETTRANSPORTFOLDER		8

/**
   \details OptionsData has fixed response size for:
   -# Reserved: uint8_t
   -# OptionsInfo: uint16_t part of SBinary_short
   -# HelpFileSize: uint16_t
 */
#define	SIZE_DFLT_ROPOPTIONSDATA		5

/**
   \details FindRow has fixed response size for:
   -# RowNoLongerVisible: uint8_t
   -# HasRowData: uint8_t
 */
#define	SIZE_DFLT_ROPFINDROW			2

/**
   \details GetPropertyIdsFromNames has fixed response size for:
   -# count: uint16_t
 */
#define	SIZE_DFLT_ROPGETPROPERTYIDSFROMNAMES	2

/**
   \details DeleteMessage Rop has fixed response size for:
   -# PartialCompletion: uint8_t
 */
#define	SIZE_DFLT_ROPDELETEMESSAGE		1


/**
   \details GetPerUserLongTermIds has fixed response size for:
   -# LongTermIdCount: uint16_t
 */
#define	SIZE_DFLT_ROPGETPERUSERLONGTERMIDS	2


/**
   \details GetPerUserGuid has fixed response size for:
   -# DatabaseGuid: uint8_t * 16
 */
#define	SIZE_DFLT_ROPGETPERUSERGUID		16


/**
   \details LogonRop has a fixed size for mailbox:
   -# LogonFlags: uint8_t
   -# FolderIDs: uint64_t * 13
   -# ResponseFlags: uint8_t
   -# MailboxGUID: sizeof (struct GUID)
   -# ReplID: uint16_t
   -# ReplGUID: sizeof (struct GUID)
   -# LogonTime: uint8_t * 6 + uint16_t
   -# GwartTime: uint64_t
   -# StoreState: uint32_t
 */
#define	SIZE_DFLT_ROPLOGON_MAILBOX	160

/**
   \details LogonRop has a fixed size for public folder logon:
   -# LogonFlags: uint8_t
   -# FolderIDs: uint64_t * 13
   -# ReplId: uint16_t
   -# ReplGuid: sizeof (struct GUID) = 16 bytes
   -# PerUserGuid: sizeof (struct GUID) = 16 bytes
 */
#define	SIZE_DFLT_ROPLOGON_PUBLICFOLDER	139

/**
   \details LogonRop has a fixed size for redirect response:
   -# LogonFlags: uint8_t
   -# ServerNameSize: uint8_t
 */
#define	SIZE_DFLT_ROPLOGON_REDIRECT	2

#define	SIZE_NULL_TRANSACTION		2

/**
   \details LongTermId structure is fixed size:
   -# DatabaseGUID: uint8_t * 16
   -# GlobalCounter: uint8_t * 6
   -# padding: uint16_t
 */
#define	SIZE_DFLT_LONGTERMID		24

__BEGIN_DECLS

/* definitions from libmapiserver_oxcfold.c */
uint16_t libmapiserver_RopOpenFolder_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopGetHierarchyTable_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopGetContentsTable_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopCreateFolder_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopDeleteFolder_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopDeleteMessage_size(struct EcDoRpc_MAPI_REPL *);

/* definitions from libmapiserver_oxcmsg.c */
uint16_t libmapiserver_RopOpenMessage_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopCreateMessage_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopSaveChangesMessage_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopModifyRecipients_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopSetMessageReadFlag_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopGetAttachmentTable_size(struct EcDoRpc_MAPI_REPL *);

/* definitions from libmapiserver_oxcnotif.c */
uint16_t libmapiserver_RopRegisterNotification_size(void);

/* definitions from libmapiserver_oxcdata.c */
uint16_t libmapiserver_TypedString_size(struct TypedString);
uint16_t libmapiserver_RecipientRow_size(struct RecipientRow);
uint16_t libmapiserver_LongTermId_size(void);

/* definitions from libmapiserver_oxcprpt.c */
uint16_t libmapiserver_RopSetProperties_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopDeleteProperties_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopGetPropertiesSpecific_size(struct EcDoRpc_MAPI_REQ *, struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopOpenStream_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopGetPropertyIdsFromNames_size(struct EcDoRpc_MAPI_REPL *);
int libmapiserver_push_property(TALLOC_CTX *, struct smb_iconv_convenience *, uint32_t, const void *, DATA_BLOB *, uint8_t, uint8_t);
struct SRow *libmapiserver_ROP_request_to_properties(TALLOC_CTX *, void *, uint8_t);

/* definitions from libmapiserver_oxcstor.c */
uint16_t libmapiserver_RopLogon_size(struct EcDoRpc_MAPI_REQ *, struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopRelease_size(void);
uint16_t libmapiserver_RopGetReceiveFolder_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopGetPerUserLongTermIds_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopGetPerUserGuid_size(struct EcDoRpc_MAPI_REPL *);

/* definitions from libmapiserver_oxctabl.c */
uint16_t libmapiserver_RopSetColumns_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopSortTable_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopRestrict_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopQueryRows_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopQueryPosition_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopSeekRow_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopFindRow_size(struct EcDoRpc_MAPI_REPL *);

/* definitions from libmapiserver_oxomsg.c */
uint16_t libmapiserver_RopSubmitMessage_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopSetSpooler_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopGetAddressTypes_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopGetTransportFolder_size(struct EcDoRpc_MAPI_REPL *);
uint16_t libmapiserver_RopOptionsData_size(struct EcDoRpc_MAPI_REPL *);

/* definitions from libmapiserver_oxorule.c */
uint16_t libmapiserver_RopGetRulesTable_size(void);

/* definitions from libmapiserver_oxcperm.c */
uint16_t libmapiserver_RopGetPermissionsTable_size(struct EcDoRpc_MAPI_REPL *);

__END_DECLS

#endif /* ! __LIBMAPISERVER_H__ */
