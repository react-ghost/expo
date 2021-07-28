import * as React from 'react';

import VideoPlayer from './components/VideoPlayer';

export const VideoHttpPlayer = () => (
  <VideoPlayer
    sources={[
      { uri: 'http://d23dyxeqlo5psv.cloudfront.net/big_buck_bunny.mp4' },
      { uri: 'http://techslides.com/demos/sample-videos/small.mp4' },
      { uri: 'http://qthttp.apple.com.edgesuite.net/1010qwoeiuryfg/sl.m3u8' },
    ]}
  />
);

VideoHttpPlayer.storyConfig = {
  name: 'Play Remote Videos',
};

export const LocalAssetPlayer = () => (
  <VideoPlayer
    sources={[require('./assets/videos/ace.mp4'), require('./assets/videos/star.mp4')]}
  />
);

LocalAssetPlayer.storyConfig = {
  name: 'Play Local Videos',
};

export default {
  title: 'Video',
};
