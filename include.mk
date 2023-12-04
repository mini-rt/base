SUFFIX :=

MINIRT_PRECISION ?= float
ifeq ($(MINIRT_PRECISION),float)
    DMINIRT_PRECISION := 1
else ifeq ($(MINIRT_PRECISION),double)
    DMINIRT_PRECISION := 2
else ifeq ($(MINIRT_PRECISION),long double)
    DMINIRT_PRECISION := 3
else
    $(error Unrecognized MINIRT_PRECISION: $(MINIRT_PRECISION))
endif
CPPFLAGS += -DMINIRT_PRECISION=$(DMINIRT_PRECISION)
SUFFIX := $(SUFFIX).precision=$(DMINIRT_PRECISION)

TARGET ?= production
ifeq ($(TARGET),production)
    DTARGET := PRODUCTION
else ifeq ($(TARGET),development)
    DTARGET := DEVELOPMENT
else
    $(error Unrecognized TARGET: $(TARGET))
endif
CPPFLAGS += -D$(DTARGET)
SUFFIX := $(SUFFIX).target=$(TARGET)

PROFILE ?= release
ifeq ($(PROFILE),release)
    DPROFILE := NDEBUG
else ifeq ($(PROFILE),debug)
    DPROFILE := DEBUG
else
    $(error Unrecognized PROFILE: $(PROFILE))
endif
CPPFLAGS += -D$(DPROFILE)
SUFFIX := $(SUFFIX).profile=$(PROFILE)
