#include <string>
#include <iostream>

using namespace std;

#ifndef PLAYLIST_H
#define PLAYLIST_H

class PlaylistNode {
 public:
    PlaylistNode();
    PlaylistNode(string, string, string, int);
    void InsertAfter(PlaylistNode*);
    void SetNext(PlaylistNode*);
    string GetID() const;
    string GetSongName() const;
    string GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode * GetNext() const;
    void PrintPlaylistNode();
 private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode * nextNodePtr;
};

//Edward Zhu helped me with this idea
class Playlist {
 public:
   Playlist(string);
   void OutputFullPlaylist();
   void AddSong();
   void RemoveSong(string);
   void ChangePosition(int, int);
   void OutputSongsSpecificArtist(string);
   void OutputTotalTime();
   //void cheatAdd(string, string, string, int);
 private:
   string title;
   PlaylistNode* head;
   PlaylistNode* tail;
};

#endif