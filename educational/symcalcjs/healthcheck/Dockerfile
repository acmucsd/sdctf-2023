# Copyright 2020 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
FROM gcr.io/kctf-docker/healthcheck@sha256:06c6f051583b84d8dc4d77962256b7d1f1f247f405972e0649c821837b66c894
RUN apt-get update \
    && apt-get -yq --no-install-recommends install python3-pip \
    && rm -rf /var/lib/apt/lists/* \
    && python3 -m pip install requests

COPY healthcheck_loop.sh healthcheck.py healthz_webserver.py /home/user/

CMD kctf_drop_privs /home/user/healthcheck_loop.sh & /home/user/healthz_webserver.py
