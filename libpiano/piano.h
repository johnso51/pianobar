/*
Copyright (c) 2008 Lars-Dominik Braun

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef _PIANO_H
#define _PIANO_H

/* this is our public API
 * all strings _must_ be utf-8 encoded. i won't care, but pandora does. so
 * be nice and check the encoding of your strings. thanks :) */

#include <curl/curl.h>

struct PianoUserInfo {
	unsigned int zipcode;
	/* disabled: billingFrequency */
	signed hasExplicitContentFilter;
	char *webAuthToken;
	/* disabled: alertCode */
	/* disabled: seenQuickMixPanel */
	unsigned short birthYear;
	char *bookmarkUrl;
	char *listenerState; /* FIXME: use enum? */
	/* disabled: adCookieValue */
	/* disabled: gender */
	/* disabled: emailOptIn */
	/* disabled: autoRenew */
	char *username;
	char *listenerId;
	char *authToken;
	char *webName;
};

typedef struct PianoUserInfo PianoUserInfo_t;

struct PianoStation {
	signed isCreator;
	/* disabled: originalStationId */
	char **genre;
	unsigned int originalCreatorId;
	/* disabled: initialSeed */
	/* disabled: isNew */
	/* disabled: transformType */
	char *idToken;
	signed isQuickMix;
	char *name;
	char *id;
	struct PianoStation *next;
};

typedef struct PianoStation PianoStation_t;

struct PianoSong {
	char *artist;
	char **genre;
	char *matchingSeed;
	/* disabled: composerName */
	/* disabled: isSeed */
	/* disabled: artistFansURL */
	/* disabled: songExplorerUrl */
	float fileGain;
	/* disabled: songDetailURL */
	/* disabled: albumDetailURL */
	char *webId;
	/* disabled: musicComUrl */
	/* disabled: fanExplorerUrl */
	int rating;
	/* disabled: artistExplorerUrl */
	/* disabled: artRadio */
	char *audioEncoding; /* FIXME: should be enum: mp3 or aacplus */
	char *stationId;
	char *album;
	char *artistMusicId;
	char *userSeed;
	/* disabled: albumExplorerUrl */
	/* disabled: amazonUrl */
	char *audioUrl;
	signed onTour;
	/* disabled: itunesUrl */
	char *musicId;
	char *title;
	char *focusTraitId;
	char *identity;
	struct PianoSong *next;
};

typedef struct PianoSong PianoSong_t;

struct PianoHandle {
	CURL *curlHandle;
	char routeId[9];
	PianoUserInfo_t user;
	/* linked lists */
	PianoStation_t *stations;
	PianoSong_t *playlist;
};

typedef struct PianoHandle PianoHandle_t;

enum PianoSongRating {PIANO_RATE_BAN, PIANO_RATE_LOVE};
typedef enum PianoSongRating PianoSongRating_t;

void PianoInit (PianoHandle_t *);
void PianoDestroy (PianoHandle_t *);
void PianoDestroyPlaylist (PianoHandle_t *ph);
void PianoConnect (PianoHandle_t *, char *, char *);

void PianoGetStations (PianoHandle_t *ph);
void PianoGetPlaylist (PianoHandle_t *ph, char *stationId);

void PianoRateTrack (PianoHandle_t *ph, PianoStation_t *station,
		PianoSong_t *song, PianoSongRating_t rating);

#endif /* _PIANO_H */
