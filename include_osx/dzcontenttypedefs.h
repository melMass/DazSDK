/**********************************************************************
	Copyright (C) 2002-2012 DAZ 3D, Inc. All Rights Reserved.

	This file is part of the DAZ Studio SDK.

	This file may be used only in accordance with the DAZ Studio SDK
	license provided with the DAZ Studio SDK.

	The contents of this file may not be disclosed to third parties,
	copied or duplicated in any form, in whole or in part, without the
	prior written permission of DAZ 3D, Inc, except as explicitly
	allowed in the DAZ Studio SDK license.

	See http://www.daz3d.com to contact DAZ 3D or for more
	information about the DAZ Studio SDK.
**********************************************************************/

/**
	@sdk
	@file
	General definitions for content types used frequently in Studio.
**/
#ifndef DAZ_CONTENT_TYPE_DEFS_H
#define DAZ_CONTENT_TYPE_DEFS_H

/*****************************
	Includes
*****************************/
#include <QtCore/QString>

//////////////////////////////////////////////////////////////////////////
// Content Types
//////////////////////////////////////////////////////////////////////////

// The following list of string constants should match ContentTypes.txt.
// It's currently a subset, but eventually all entries should be moved into constants.

// Actor Types
const QString DZ_ACTOR_TYPE( "Actor" );

// Camera Types
const QString DZ_CAMERA_TYPE( "Camera" );

// Follower Types
const QString DZ_FOLLOWER_TYPE( "Follower" );
const QString DZ_FOLLOWER_ACCESSORY_TYPE( "Follower/Accessory" );
const QString DZ_FOLLOWER_ATTACHMENT_TYPE( "Follower/Attachment" );
const QString DZ_FOLLOWER_HAIR_TYPE( "Follower/Hair" );
const QString DZ_FOLLOWER_WARDROBE_TYPE( "Follower/Wardrobe" );

// Light Types
const QString DZ_LIGHT_TYPE( "Light" );

// Modifier Types
const QString DZ_MODIFIER_TYPE( "Modifier" );
const QString DZ_MODIFIER_CLONE_TYPE( "Modifier/Clone" );
const QString DZ_MODIFIER_GENERATED_SUFFIX_TYPE( "/Generated" );
const QString DZ_MODIFIER_POSE_TYPE( "Modifier/Pose" );
const QString DZ_MODIFIER_SHAPE_TYPE( "Modifier/Shape" );
const QString DZ_MODIFIER_SHAPE_GENERATED_TYPE( "Modifier/Shape/Generated" );

// Preset Types
const QString DZ_PRESET_TYPE( "Preset" );
const QString DZ_PRESET_ANIMATION_TYPE( "Preset/Animation" );
const QString DZ_PRESET_CAMERA_TYPE( "Preset/Camera" );
const QString DZ_PRESET_CHARACTER_TYPE( "Preset/Character" );
const QString DZ_PRESET_DEFORMER_TYPE( "Preset/Deformer" );
const QString DZ_PRESET_FACE_TYPE( "Preset/Face" );
const QString DZ_PRESET_HAND_TYPE( "Preset/Hand" );
const QString DZ_PRESET_LAYERED_IMAGE_TYPE( "Preset/Layered-Image" );
const QString DZ_PRESET_LIGHT_TYPE( "Preset/Light" );
const QString DZ_PRESET_MATERIALS_TYPE( "Preset/Materials" );
const QString DZ_PRESET_MATERIALS_HIERARCHICAL_TYPE( "Preset/Materials/Hierarchical" );
const QString DZ_PRESET_MORPH_TYPE( "Preset/Morph" );
const QString DZ_PRESET_MORPH_APPLY_TYPE( "Preset/Morph/Apply" );
const QString DZ_PRESET_POSE_TYPE( "Preset/Pose" );
const QString DZ_PRESET_PROPERTIES_TYPE( "Preset/Properties" );
const QString DZ_PRESET_PUPPETEER_TYPE( "Preset/Puppeteer" );
const QString DZ_PRESET_SHADER_TYPE( "Preset/Shader" );
const QString DZ_PRESET_UV_TYPE( "Preset/UV" );
const QString DZ_PRESET_WEARABLES_TYPE( "Preset/Wearables" );
const QString DZ_PRESET_RENDER_SETTINGS_TYPE( "Preset/Render-Settings" );

// Prop Types
const QString DZ_PROP_TYPE( "Prop" );
const QString DZ_PROP_HAIR_TYPE( "Prop/Hair" );

// Scene Types
const QString DZ_SCENE_TYPE( "Scene" );

// Set Types
const QString DZ_SET_TYPE( "Set" );


//////////////////////////////////////////////////////////////////////////
// Root Categories
//////////////////////////////////////////////////////////////////////////

// The following list of string constants should match RootCategories.txt.
// It's currently a subset, but eventually all entries should be moved into constants.

const QString DZ_PEOPLE_CATEGORY( "People" );
const QString DZ_ACCESSORIES_CATEGORY( "Accessories" );
const QString DZ_ANIMALS_CATEGORY( "Animals" );
const QString DZ_CREATURES_CATEGORY( "Creatures" );
const QString DZ_HAIR_CATEGORY( "Hair" );
const QString DZ_UNASSIGNED_CATEGORY( "Default/Unassigned" );

const QString DZ_PRESETS_CATEGORY( "Presets" );
const QString DZ_PRESETS_ANIMATIONS_CATEGORY( "Presets/Animations" );
const QString DZ_PRESETS_CAMERAS_CATEGORY( "Presets/Cameras" );
const QString DZ_PRESETS_LIGHTS_CATEGORY( "Presets/Lights" );
const QString DZ_PRESETS_MATERIALS_CATEGORY( "Presets/Materials" );
const QString DZ_PRESETS_MORPHS_CATEGORY( "Presets/Morphs" );
const QString DZ_PRESETS_POSES_CATEGORY( "Presets/Poses" );
const QString DZ_PRESETS_SHADER_CATEGORY( "Presets/Shader" );

const QString DZ_PROPS_CATEGORY( "Props" );
const QString DZ_SCENES_CATEGORY( "Scenes" );
const QString DZ_SETS_CATEGORY( "Sets" );
const QString DZ_WARDROBE_CATEGORY( "Wardrobe" );

//////////////////////////////////////////////////////////////////////////
// Special Compatibilities
//////////////////////////////////////////////////////////////////////////

// The following list of string constants should match CompatibilityBases.txt.
// It's currently a subset.

const QString DZ_ANY_OBJECT_COMPATIBILITYBASE("AnyObject");
const QString DZ_ANY_SURFACE_COMPATIBILITYBASE("AnySurface");

#endif