/******************************************************************************
 *  CVS version:
 *     $Id: symbol.h,v 1.1 2003/05/13 22:21:01 nickie Exp $
 ******************************************************************************
 *
 *  C header file : symbol.h
 *  Project       : PCL Compiler
 *  Version       : 1.0 alpha
 *  Written by    : Nikolaos S. Papaspyrou (nickie@softlab.ntua.gr)
 *  Date          : May 14, 2003
 *  Description   : Generic symbol table in C
 *
 *  Comments: (in Greek iso-8859-7)
 *  ---------
 *  Åèíéêü Ìåôóüâéï Ðïëõôå÷íåßï.
 *  Ó÷ïëÞ Çëåêôñïëüãùí Ìç÷áíéêþí êáé Ìç÷áíéêþí Õðïëïãéóôþí.
 *  ÔïìÝáò Ôå÷íïëïãßáò ÐëçñïöïñéêÞò êáé Õðïëïãéóôþí.
 *  ÅñãáóôÞñéï Ôå÷íïëïãßáò Ëïãéóìéêïý
 */


#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__


/* ---------------------------------------------------------------------
   -------------------------- Ôýðïò bool -------------------------------
   --------------------------------------------------------------------- */

#include <stdbool.h>

/*
 *  Áí ôï ðáñáðÜíù include äåí õðïóôçñßæåôáé áðü ôçí õëïðïßçóç
 *  ôçò C ðïõ ÷ñçóéìïðïéåßôå, áíôéêáôáóôÞóôå ôï ìå ôï áêüëïõèï:
 */

#if 0
typedef enum { false=0, true=1 } bool;
#endif


/* ---------------------------------------------------------------------
   ------------ Ïñéóìüò óôáèåñþí ôïõ ðßíáêá óõìâüëùí -------------------
   --------------------------------------------------------------------- */

#define START_POSITIVE_OFFSET 8     /* Áñ÷éêü èåôéêü offset óôï Å.Ä.   */
#define START_NEGATIVE_OFFSET 0     /* Áñ÷éêü áñíçôéêü offset óôï Å.Ä. */


/* ---------------------------------------------------------------------
   --------------- Ïñéóìüò ôýðùí ôïõ ðßíáêá óõìâüëùí -------------------
   --------------------------------------------------------------------- */

/* Ôýðïé äåäïìÝíùí ãéá ôçí õëïðïßçóç ôùí óôáèåñþí */

typedef int           RepInteger;         /* ÁêÝñáéåò                  */
typedef unsigned char RepBoolean;         /* ËïãéêÝò ôéìÝò             */
typedef char          RepChar;            /* ×áñáêôÞñåò                */
typedef long double   RepReal;            /* ÐñáãìáôéêÝò               */
typedef const char *  RepString;          /* ÓõìâïëïóåéñÝò             */


/* Ôýðïé äåäïìÝíùí êáé áðïôåëÝóìáôïò óõíáñôÞóåùí */

typedef struct Type_tag * Type;

struct Type_tag {
    enum {                               /***** Ôï åßäïò ôïõ ôýðïõ ****/
       TYPE_VOID,                        /* Êåíüò ôýðïò áðïôåëÝóìáôïò */
       TYPE_INTEGER,                     /* ÁêÝñáéïé                  */
       TYPE_BOOLEAN,                     /* ËïãéêÝò ôéìÝò             */
       TYPE_CHAR,                        /* ×áñáêôÞñåò                */
       TYPE_ARRAY,                       /* Ðßíáêåò ãíùóôïý ìåãÝèïõò  */
       TYPE_IARRAY,                      /* Ðßíáêåò Üãíùóôïõ ìåãÝèïõò */
       TYPE_POINTER,                     /* Äåßêôåò                   */
       TYPE_NIL
    } kind;
    Type           refType;              /* Ôýðïò áíáöïñÜò            */
    RepInteger     size;                 /* ÌÝãåèïò, áí åßíáé ðßíáêáò */
    unsigned int   refCount;             /* ÌåôñçôÞò áíáöïñþí         */
};


/* Ôýðïé åããñáöþí ôïõ ðßíáêá óõìâüëùí */

typedef enum {            
   ENTRY_VARIABLE,                       /* ÌåôáâëçôÝò                 */
   ENTRY_CONSTANT,                       /* ÓôáèåñÝò                   */
   ENTRY_FUNCTION,                       /* ÓõíáñôÞóåéò                */
   ENTRY_PARAMETER,                      /* ÐáñÜìåôñïé óõíáñôÞóåùí     */
   ENTRY_TEMPORARY                       /* ÐñïóùñéíÝò ìåôáâëçôÝò      */
} EntryType;


/* Ôýðïé ðåñÜóìáôïò ðáñáìåôñùí */

typedef enum {            
   PASS_BY_VALUE,                        /* Êáô' áîßá                  */
   PASS_BY_REFERENCE                     /* Êáô' áíáöïñÜ               */
} PassMode;


/* Ôýðïò åããñáöÞò óôïí ðßíáêá óõìâüëùí */

typedef struct SymbolEntry_tag SymbolEntry;

struct SymbolEntry_tag {
   const char   * id;                 /* Ïíïìá áíáãíùñéóôéêïý          */
   EntryType      entryType;          /* Ôýðïò ôçò åããñáöÞò            */
   unsigned int   nestingLevel;       /* ÂÜèïò öùëéÜóìáôïò             */
   unsigned int   hashValue;          /* ÔéìÞ êáôáêåñìáôéóìïý          */
   SymbolEntry  * nextHash;           /* Åðüìåíç åããñáöÞ óôïí Ð.Ê.     */
   SymbolEntry  * nextInScope;        /* Åðüìåíç åããñáöÞ óôçí åìâÝëåéá */

   union {                            /* ÁíÜëïãá ìå ôïí ôýðï åããñáöÞò: */

      struct {                                /******* ÌåôáâëçôÞ *******/
         Type          type;                  /* Ôýðïò                 */
         int           offset;                /* Offset óôï Å.Ä.       */
      } eVariable;

      struct {                                /******** ÓôáèåñÜ ********/
         Type          type;                  /* Ôýðïò                 */
         union {                              /* ÔéìÞ                  */
            RepInteger vInteger;              /*    áêÝñáéá            */
            RepBoolean vBoolean;              /*    ëïãéêÞ             */
            RepChar    vChar;                 /*    ÷áñáêôÞñáò         */
            RepReal    vReal;                 /*    ðñáãìáôéêÞ         */
            RepString  vString;               /*    óõìâïëïóåéñÜ       */
         } value;
      } eConstant;

      struct {                                /******* ÓõíÜñôçóç *******/
         bool          isForward;             /* ÄÞëùóç forward        */
         SymbolEntry * firstArgument;         /* Ëßóôá ðáñáìÝôñùí      */
         SymbolEntry * lastArgument;          /* Ôåëåõôáßá ðáñÜìåôñïò  */
         Type          resultType;            /* Ôýðïò áðïôåëÝóìáôïò   */
         enum {                               /* ÊáôÜóôáóç ðáñáìÝôñùí  */
             PARDEF_COMPLETE,                    /* ÐëÞñçò ïñéóìüò     */
             PARDEF_DEFINE,                      /* Åí ìÝóù ïñéóìïý    */
             PARDEF_CHECK                        /* Åí ìÝóù åëÝã÷ïõ    */
         } pardef;
         int           firstQuad;             /* Áñ÷éêÞ ôåôñÜäá        */
      } eFunction;

      struct {                                /****** ÐáñÜìåôñïò *******/
         Type          type;                  /* Ôýðïò                 */
         int           offset;                /* Offset óôï Å.Ä.       */
         PassMode      mode;                  /* Ôñüðïò ðåñÜóìáôïò     */
         SymbolEntry * next;                  /* Åðüìåíç ðáñÜìåôñïò    */
      } eParameter;

      struct {                                /** ÐñïóùñéíÞ ìåôáâëçôÞ **/
         Type          type;                  /* Ôýðïò                 */
         int           offset;                /* Offset óôï Å.Ä.       */
         int           number;
      } eTemporary;

   } u;                               /* ÔÝëïò ôïõ union               */
};


/* Ôýðïò óõíüëïõ åããñáöþí ðïõ âñßóêïíôáé óôçí ßäéá åìâÝëåéá */

typedef struct Scope_tag Scope;

struct Scope_tag {
    unsigned int   nestingLevel;             /* ÂÜèïò öùëéÜóìáôïò      */
    unsigned int   negOffset;                /* ÔñÝ÷ïí áñíçôéêü offset */
    Scope        * parent;                   /* ÐåñéâÜëëïõóá åìâÝëåéá  */
    SymbolEntry  * entries;                  /* Óýìâïëá ôçò åìâÝëåéáò  */
};


/* Ôýðïò áíáæÞôçóçò óôïí ðßíáêá óõìâüëùí */

typedef enum {
    LOOKUP_CURRENT_SCOPE,
    LOOKUP_ALL_SCOPES
} LookupType;


/* ---------------------------------------------------------------------
   ------------- ÊáèïëéêÝò ìåôáâëçôÝò ôïõ ðßíáêá óõìâüëùí --------------
   --------------------------------------------------------------------- */

extern Scope        * currentScope;       /* ÔñÝ÷ïõóá åìâÝëåéá         */
extern unsigned int   quadNext;           /* Áñéèìüò åðüìåíçò ôåôñÜäáò */
extern unsigned int   tempNumber;         /* Áñßèìçóç ôùí temporaries  */

extern const Type typeVoid;
extern const Type typeInteger;
extern const Type typeBoolean;
extern const Type typeChar;
extern const Type typeReal;


/* ---------------------------------------------------------------------
   ------ Ðñùôüôõðá ôùí óõíáñôÞóåùí ÷åéñéóìïý ôïõ ðßíáêá óõìâïëþí ------
   --------------------------------------------------------------------- */

void          initSymbolTable    (unsigned int size);
void          destroySymbolTable (void);

void          openScope          (void);
void          closeScope         (void);

SymbolEntry * newVariable        (const char * name, Type type);
SymbolEntry * newConstant        (const char * name, Type type, ...);
SymbolEntry * newFunction        (const char * name);
SymbolEntry * newParameter       (const char * name, Type type,
                                  PassMode mode, SymbolEntry * f);
SymbolEntry * newTemporary       (Type type);

void          forwardFunction    (SymbolEntry * f);
void          endFunctionHeader  (SymbolEntry * f, Type type);
void          destroyEntry       (SymbolEntry * e);
SymbolEntry * lookupEntry        (const char * name, LookupType type,
                                  bool err);

Type          typeArray          (RepInteger size, Type refType);
Type          typeIArray         (Type refType);
Type          typePointer        (Type refType);
void          destroyType        (Type type);
unsigned int  sizeOfType         (Type type);
bool          equalType          (Type type1, Type type2);
void          printType          (Type type);
void          printMode          (PassMode mode);


#endif
