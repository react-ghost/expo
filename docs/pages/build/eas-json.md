---
title: Configuration with eas.json
---

import EasJsonPropertiesTable from '~/components/plugins/EasJsonPropertiesTable';

import commonSchema from '~/scripts/schemas/unversioned/eas-json-common-schema.js';
import androidSchema from '~/scripts/schemas/unversioned/eas-json-android-schema.js';
import iosSchema from '~/scripts/schemas/unversioned/eas-json-ios-schema.js';



`eas.json` is your go-to place for configuring EAS Build. It is located at the root of your project next to your `package.json`. It looks something like this:

```json
{
  "build": {
    "release": {},
    "development": {
      "developmentClient": true,
      "distribution": "internal"
    }
  }
}
```

or

```json
{
  "build": {
    "release": {},
    "development": {
      "distribution": "internal",
      "android": {
        "gradleCommand": ":app:assembleDebug"
      },
      "ios": {
        "buildConfiguration": "Debug"
      }
    }
  }
}
```

The JSON object under the `build` key can contain multiple build profiles. Every build profile can have an arbitrary name. The default profile that is expected by EAS CLI to exist is `release` (if you'd like to build your app using another build profile you need to specify it with a parameter - `eas build --platform android --profile foobar`). In the example, there are two build profiles (`release` and `development`), however they could be named `foo` or `bar` or whatever you'd like. Inside build profile you can specify `android` and `ios` fields that contain platform specific configuration for the build, any common options can be also stored there or in the root of the build profile.

Generally, the schema of this file looks like this:

<!-- prettier-ignore -->
```json
{
  "build": {
    /* @info any arbitrary name - used as an identifier */"BUILD_PROFILE_NAME_1"/* @end */: {
      /* @info options common for both platforms*/...COMMON_OPTIONS/* @end */

      android: {
        /* @info options specific for Android and common for both platforms*/...ANDROID_OPTIONS/* @end */

      }
      ios: {
        /* @info options specific for iOS and common for both platforms*/...IOS_OPTIONS/* @end */

      }
    },
    /* @info any arbitrary name - used as an identifier */"BUILD_PROFILE_NAME_2"/* @end */: {

    },
    ...,
  }
}
```

## Examples

<details>
  <summary>A managed project with several common profiles</summary>

```json
{
  "build": {
    "base": {
      "node": "12.13.0",
      "yarn": "1.22.5",
      "env": {
        "EXAMPLE_ENV": "example value"
      },
      "android": {
        "image": "default",
        "env": {
          "PLATFORM": "android"
        }
      },
      "ios": {
        "image": "latest",
        "env": {
          "PLATFORM": "ios"
        }
      }
    },
    "release": {
      "extends": "base",
      "env": {
        "ENVIRONMENT": "production"
      }
    },
    "staging": {
      "extends": "base",
      "env": {
        "ENVIRONMENT": "staging"
      },
      "distribution": "internal",
      "android": {
        "buildType": "apk"
      }
    },
    "development": {
      "extends": "base",
      "developmentClient": true,
      "env": {
        "ENVIRONMENT": "development"
      },
      "android": {
        "distribution": "internal",
        "withoutCredentials": true
      },
      "ios": {
        "simulator": true
      }
    }
  }
}
```
</details>

<details>
  <summary>A bare project with several common profiles</summary>

```json
{
  "build": {
    "base": {
      "env": {
        "EXAMPLE_ENV": "example value"
      },
      "android": {
        "image": "ubuntu-18.04-android-30-ndk-r19c",
        "ndk": "21.4.7075529"
      },
      "ios": {
        "image": "latest",
        "node": "12.13.0",
        "yarn": "1.22.5"
      }
    },
    "release": {
      "extends": "base",
      "env": {
        "ENVIRONMENT": "production"
      }
    },
    "staging": {
      "extends": "base",
      "env": {
        "ENVIRONMENT": "staging"
      },
      "distribution": "internal",
      "android": {
        "gradleCommand": ":app:assembleRelease"
      }
    },
    "development": {
      "extends": "base",
      "env": {
        "ENVIRONMENT": "staging"
      },
      "android": {
        "distribution": "internal",
        "withoutCredentials": true,
        "gradleCommand": ":app:assembleDebug"
      },
      "ios": {
        "simulator": true,
        "buildConfiguration": "Debug"
      }
    }
  }
}
```

</details>

## Common options for both paltforms

<EasJsonPropertiesTable schema={commonSchema}/>

## Android specific options

<EasJsonPropertiesTable schema={androidSchema}/>

## iOS specific options

<EasJsonPropertiesTable schema={iosSchema}/>
