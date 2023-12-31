//
// (C) Copyright 2019-2022 Intel Corporation.
//
// SPDX-License-Identifier: BSD-2-Clause-Patent
//

package logging

import (
	"fmt"
	"strings"
	"sync/atomic"
)

const (
	// LogLevelDisabled disables any logging output
	LogLevelDisabled LogLevel = iota
	// LogLevelError emits messages at ERROR or higher
	LogLevelError
	// LogLevelNotice emits messages at NOTICE or higher
	LogLevelNotice
	// LogLevelInfo emits messages at INFO or higher
	LogLevelInfo
	// LogLevelDebug emits messages at DEBUG or higher
	LogLevelDebug
	// LogLevelTrace emits messages at TRACE or higher
	LogLevelTrace

	strDisabled = "DISABLED"
	strError    = "ERROR"
	strNotice   = "NOTICE"
	strInfo     = "INFO"
	strDebug    = "DEBUG"
	strTrace    = "TRACE"
)

// LogLevel represents the level at which the logger will emit log messages
type LogLevel int32

// Set safely sets the log level to the supplied level
func (ll *LogLevel) Set(newLevel LogLevel) {
	atomic.StoreInt32((*int32)(ll), int32(newLevel))
}

// Get returns the current log level
func (ll *LogLevel) Get() LogLevel {
	return LogLevel(atomic.LoadInt32((*int32)(ll)))
}

// SetString sets the log level from the supplied string.
func (ll *LogLevel) SetString(in string) error {
	var level LogLevel

	switch {
	case strings.EqualFold(in, strDisabled):
		level = LogLevelDisabled
	case strings.EqualFold(in, strError):
		level = LogLevelError
	case strings.EqualFold(in, strNotice):
		level = LogLevelNotice
	case strings.EqualFold(in, strInfo):
		level = LogLevelInfo
	case strings.EqualFold(in, strDebug):
		level = LogLevelDebug
	case strings.EqualFold(in, strTrace):
		level = LogLevelTrace
	default:
		return fmt.Errorf("%q is not a valid log level", in)
	}

	ll.Set(level)
	return nil
}

func (ll LogLevel) String() string {
	switch ll {
	case LogLevelDisabled:
		return strDisabled
	case LogLevelError:
		return strError
	case LogLevelNotice:
		return strNotice
	case LogLevelInfo:
		return strInfo
	case LogLevelDebug:
		return strDebug
	case LogLevelTrace:
		return strTrace
	default:
		return "UNKNOWN"
	}
}
